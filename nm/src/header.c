/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 10:46:29 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/23 11:32:36 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int	error_deref(char *str)
{
	ft_putstr_fd("ft_nm : ", 2);
	ft_putendl_fd(str, 2);
	return (-1);
}

int	process_header(t_infile *infile)
{
	unsigned long magic_bytes;

	magic_bytes = 0;
	if ((void *)infile->mem + sizeof(unsigned long)
			> (void *)infile->mem + infile->sz)
		return (error_deref("corrupted header file"));
	magic_bytes = (unsigned long)infile->mem + sizeof(unsigned long);
	printf("magic bytes : %lu", magic_bytes);
	return (0);
}
