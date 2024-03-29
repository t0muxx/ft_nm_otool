/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:46:49 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/14 14:38:58 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "libft.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/mman.h>

# ifdef __linux__
#  include "../mach_headers/custom.h"
# else
#  include <mach-o/loader.h>
#  include <mach-o/nlist.h>
#  include <mach/machine.h>
#  include <mach-o/fat.h>
#  include <ar.h>
#  include <ranlib.h>
# endif

# define IS_32 1
# define IS_64 2
# define IS_BE 3
# define IS_BE_64 4

typedef	struct	s_section
{
	void				*section;
	int					id;
	struct s_section	*next;

}				t_section;

typedef struct	s_symbol
{
	void				*symbol;
	char				*symbol_name;
	char				symb_char;
	uint64_t			symb_value;
	struct s_symbol		*next;

}				t_symbol;

typedef	struct	s_infile
{
	char					*filename;
	uint8_t					type;
	void					*start;
	void					*save;
	void					*current;
	size_t					sz;
	uint64_t				ar_sz;
	void					*mac_header;
	struct symtab_command	*symtab_command;
	t_section				*sections;
	t_symbol				*symbols;

}				t_infile;

int				protect(t_infile *file, void *ptr);
int				error_gen(char *str);
size_t			protected_strlen(char *str, t_infile *file);
void			protected_free(t_infile *file);

int				process_archive(t_infile *file);
int				process_fat(t_infile *file);
int				process_macho(t_infile *infile);
t_infile		*process_infile(char *path);
int				process_header(t_infile *infile);

int				iter_load_command(t_infile *infile);

int				parse_segment(t_infile *file, struct load_command *lc);
int				parse_symtab(t_infile *file,
									struct symtab_command *symtab_command);
void			symbol_resolve(t_infile *infile);
/*
** t_section list :
*/
void			lst_section_append(t_section **head, t_section *new);
t_section		*lst_section_new(void *ptr, int id);
void			lst_section_free(t_section *head);

/*
** t_symbol list :
*/
void			lst_symbol_append(t_symbol **head, t_symbol *new);
void			lst_symbol_append_nosort(t_symbol **head, t_symbol *new);
t_symbol		*lst_symbol_new(void *ptr, char *str,
								size_t str_len, uint64_t val);
void			lst_symbol_free(t_symbol *head);
void			lst_symbol_print_32(t_symbol *head);
void			lst_symbol_print_64(t_symbol *head);
void			lst_symbol_sort(t_symbol *start);

uint64_t		reverse_64(uint8_t should, uint64_t num);
uint32_t		reverse_32(uint8_t should, uint32_t num);
uint8_t			reverse_8(uint8_t should, uint8_t num);

int				print_archive_member(t_infile *file, struct ar_hdr *ar_header);
int				get_str_offset_archive(t_infile *file,
													struct ar_hdr *ar_header);
void			putstr_member_name(char *str, size_t len);

int				search_cputype_x64(t_infile *file, unsigned long magic_bytes);
void			fat_print_arch(t_infile *file, cpu_type_t cputype,
						cpu_subtype_t cpusubtype);
#endif
