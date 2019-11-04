/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 10:46:29 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/04 16:31:54 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int	process_header_full(t_infile *infile)
{
	if (infile->type == IS_32 || infile->type == IS_BE)
	{
		if (protect(infile, (void *)infile->start
		+ sizeof(struct mach_header)) < 0)
			return (error_gen("file size inferior to header size"));
	}
	if (infile->type == IS_64 || infile->type == IS_BE_64)
	{
		if (protect(infile, (void *)infile->start
		+ sizeof(struct mach_header_64)) < 0)
			return (error_gen("file size inferior to header size"));
	}
	infile->mac_header = infile->start;
	if (infile->type == IS_32 || infile->type == IS_BE)
		infile->current = (void *)infile->start + sizeof(struct mach_header);
	if (infile->type == IS_64 || infile->type == IS_BE_64)
		infile->current = (void *)infile->start + sizeof(struct mach_header_64);
	return (0);
}

int	process_header(t_infile *infile)
{
	unsigned long magic_bytes;

	magic_bytes = 0;
	if (protect(infile, (void *)infile->start + sizeof(uint32_t)) < 0)
		return (error_gen("corrupted header file"));
	magic_bytes = *(uint32_t *)infile->start;
	if (magic_bytes == MH_MAGIC)
		infile->type = IS_32;
	else if (magic_bytes == MH_MAGIC_64)
		infile->type = IS_64;
	else if (magic_bytes == MH_CIGAM)
		infile->type = IS_BE;
	else if (magic_bytes == MH_CIGAM_64)
		infile->type = IS_BE_64;
	else
		return (-1);
	return (process_header_full(infile));
}
