/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:46:49 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/22 16:50:36 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM__H
# define FT_NM__H

# include "libft.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/mman.h>

typedef	struct	s_infile
{
	void	*mem;
	size_t	sz;

}				t_infile;

t_infile	*process_infile(char *path);

#endif
