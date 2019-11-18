/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:46:49 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/14 14:49:00 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

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

typedef	struct		s_infile
{
	char					*filename;
	uint8_t					type;
	uint8_t					type_printed;
	void					*start;
	void					*save;
	void					*current;
	cpu_type_t				cputype;
	cpu_subtype_t			cpusubtype;
	uint64_t				text_sz;
	uint64_t				text_offs;
	uint64_t				text_addr;
	size_t					sz;
	uint64_t				ar_sz;
	void					*mac_header;

}					t_infile;

void				print_text(t_infile *file);
void				print_file_type(t_infile *file, char *type);
int					print_text_bytes(t_infile *file,
										uint8_t *current, uint32_t print);
int					protect(t_infile *file, void *ptr);
int					error_gen(char *str);
size_t				protected_strlen(char *str, t_infile *file);
void				protected_free(t_infile *file);

int					process_archive(t_infile *file);
int					process_fat(t_infile *file);
int					process_macho(t_infile *infile);
t_infile			*process_infile(char *path);
int					process_header(t_infile *infile);

int					iter_load_command(t_infile *infile);

int					parse_segment(t_infile *file, struct load_command *lc);
int					parse_symtab(t_infile *file,
									struct symtab_command *symtab_command);
void				symbol_resolve(t_infile *infile);

uint64_t			reverse_64(uint8_t should, uint64_t num);
uint32_t			reverse_32(uint8_t should, uint32_t num);
uint8_t				reverse_8(uint8_t should, uint8_t num);

int					print_archive_member(t_infile *file,
											struct ar_hdr *ar_header);
int					get_str_offset_archive(t_infile *file,
												struct ar_hdr *ar_header);
void				putstr_member_name(char *str, size_t len);

int					search_cputype_x64(t_infile *file,
													unsigned long magic_bytes);
void				fat_print_arch(t_infile *file, cpu_type_t cputype,
						cpu_subtype_t cpusubtype);
#endif
