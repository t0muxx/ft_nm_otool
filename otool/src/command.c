/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:55:10 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/05 15:44:14 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int			parse_load_command(t_infile *infile, struct load_command *lc)
{
	uint32_t cmd_type;

	cmd_type = reverse_32(infile->type == IS_BE || infile->type == IS_BE_64,
			lc->cmd);
	if (protect(infile, (void *)lc + sizeof(uint32_t)) < 0)
		return (-1);
	if (cmd_type == LC_SEGMENT || cmd_type == LC_SEGMENT_64)
	{
		if (parse_segment(infile, lc) < 0)
			return (-1);
	}
	else if (cmd_type == LC_SYMTAB)
	{
		if (parse_symtab(infile, (struct symtab_command *)lc) < 0)
			return (-1);
	}
	return (0);
}

uint32_t	get_load_command_num(t_infile *infile)
{
	uint32_t	n_lcmds;

	n_lcmds = 0;
	if (infile->type == IS_32)
		n_lcmds = ((struct mach_header *)infile->mac_header)->ncmds;
	if (infile->type == IS_64)
		n_lcmds = ((struct mach_header_64 *)infile->mac_header)->ncmds;
	if (infile->type == IS_BE)
	{
		n_lcmds = reverse_32(1,
				((struct mach_header *)infile->mac_header)->ncmds);
	}
	if (infile->type == IS_BE_64)
	{
		n_lcmds = reverse_32(1,
				((struct mach_header_64 *)infile->mac_header)->ncmds);
	}
	return (n_lcmds);
}

int			check_totalsize_load_command(t_infile *file, uint32_t totalsize)
{
	if (file->type == IS_32 || file->type == IS_BE)
	{
		if (totalsize + sizeof(struct load_command)
			> ((struct mach_header *)file->mac_header)->sizeofcmds)
			return (-1);
	}
	if (file->type == IS_64 || file->type == IS_BE_64)
	{
		if (totalsize + sizeof(struct load_command)
			> ((struct mach_header_64 *)file->mac_header)->sizeofcmds)
			return (-1);
	}
	return (0);
}

int			iter_load_command_work(t_infile *infile, void *lc,
		uint32_t *cmdsize, uint32_t totalsize)
{
	if (protect(infile, (void *)lc
	+ sizeof(((struct load_command *)lc)->cmdsize)) < 0)
		return (error_gen("corrupted load commands"));
	*cmdsize = reverse_32(
		infile->type == IS_BE || infile->type == IS_BE_64,
		((struct load_command *)lc)->cmdsize);
	if (check_totalsize_load_command(infile, totalsize) < 0)
		return (error_gen("corrupted load commands"));
	if (parse_load_command(infile, (struct load_command *)lc) < 0)
		return (error_gen("corrupted load commands"));
	if (protect(infile, (void *)lc + sizeof(uint32_t)) < 0)
		return (error_gen("corrupted load commands"));
	return (0);
}

int			iter_load_command(t_infile *infile)
{
	uint32_t			n_lcmds;
	void				*lc;
	uint32_t			cmdsize;
	uint32_t			totalsize;

	lc = NULL;
	n_lcmds = get_load_command_num(infile);
	lc = (struct load_command *)infile->current;
	totalsize = 0;
	while (n_lcmds)
	{
		if (iter_load_command_work(infile, lc, &cmdsize, totalsize) < 0)
			return (-1);
		if (cmdsize <= 0)
			return (error_gen("cmdsize <= 0"));
		lc = (void *)lc + cmdsize;
		totalsize += cmdsize;
		n_lcmds--;
	}
	return (0);
}
