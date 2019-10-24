/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:46:49 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/24 13:58:00 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM__H
# define FT_NM__H

# include "libft.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/mman.h>

# ifdef __linux__
#	include "../mach_headers/custom.h"
# else
#	include <mach-o/loader.h>
#	include <mach-o/nlist.h>
# endif

# define IS_32 1
# define IS_64 2
# define IS_BE 3
# define IS_BE_64 4

# define DEBUG_HEADER
# define DEBUG_SEGMENT

typedef	struct	s_section
{
	void				*section;
	int					id;
	struct s_section	*next;

}				t_section;

typedef	struct	s_infile
{
	uint8_t		type;
	void		*start;
	void		*current;
	size_t		sz;
	void		*mac_header;
	t_section	*sections;
	void		*symtab_command;

}				t_infile;

t_infile	*process_infile(char *path);
int			process_header(t_infile *infile);
int			error_gen(char *str);
int			iter_load_command(t_infile *infile);

void		parse_segment(t_infile *file, struct load_command *lc);

/*
** t_section list :
*/
void		lst_section_append(t_section **head, t_section *new);
t_section	*lst_section_new(void *ptr, int id);
void		lst_section_free(t_section *head);

#endif
