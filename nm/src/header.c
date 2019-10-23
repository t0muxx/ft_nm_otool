/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 10:46:29 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/23 15:50:00 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int	error_gen(char *str)
{
	ft_putstr_fd("ft_nm : ", 2);
	ft_putendl_fd(str, 2);
	return (-1);
}

int	process_header_full(t_infile *infile)
{
	if (infile->type == IS_32 || infile->type == IS_BE )
	{
		if ((void *)infile->mem + sizeof(struct mach_header)
				> (void *)infile->mem + infile->sz)
			return (error_gen("file size inferior to header size"));
	}
	if (infile->type == IS_64 || infile->type == IS_BE_64)
	{
		if ((void *)infile->mem + sizeof(struct mach_header_64)
				> (void *)infile->mem + infile->sz)
			return (error_gen("file size inferior to header size"));
	}
	infile->mac_header = infile->mem;
	if (infile->type == IS_32 || infile->type == IS_BE)
		infile->mem = (void *)infile->mem + sizeof(struct mach_header);
	if (infile->type == IS_64 || infile->type == IS_BE_64)
		infile->mem = (void *)infile->mem + sizeof(struct mach_header_64);
	return (0);
}

int	process_header(t_infile *infile)
{
	unsigned long magic_bytes;

	magic_bytes = 0;
	if ((void *)infile->mem + sizeof(unsigned long)
			> (void *)infile->mem + infile->sz)
		return (error_gen("corrupted header file"));
	magic_bytes = *(uint32_t *)infile->mem;
	printf("magic bytes : %#lx\n", magic_bytes);
	if (magic_bytes == MH_MAGIC)
		infile->type = IS_32;
	else if (magic_bytes  == MH_MAGIC_64)
		infile->type = IS_64;
	else if (magic_bytes == MH_CIGAM)
		infile->type = IS_BE;
	else if (magic_bytes == MH_CIGAM_64)
		infile->type = IS_BE_64;
	else 
		return (error_gen("unknown magic byte"));
#ifdef DEBUG_HEADER
	ft_printf("|DEBUG| -> type = %d\n", infile->type);
#endif
	return (process_header_full(infile));
}
