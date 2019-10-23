/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:46:49 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/23 15:52:58 by tmaraval         ###   ########.fr       */
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

typedef	struct	s_infile
{
	uint8_t	type;
	void	*mem;
	size_t	sz;
	void	*mac_header;
	void	*segment_command;
	void	*symtab_command;

}				t_infile;

t_infile	*process_infile(char *path);
int			process_header(t_infile *infile);

#endif
