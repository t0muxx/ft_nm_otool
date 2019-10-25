/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:55:10 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/25 14:48:39 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int	parse_load_command(t_infile *infile, struct load_command *lc)
{
	if ((void *)lc + sizeof(uint32_t) > (void *)infile->start + infile->sz)
		return (-1);
	// Need to reverse bits :
	if (lc->cmd == LC_SEGMENT || lc->cmd == LC_SEGMENT_64)
	{
		if (parse_segment(infile, lc) < 0)
			return (-1);
	}
	else if (lc->cmd == LC_SYMTAB)
	{
		if (parse_symtab(infile, (struct symtab_command *)lc) < 0)
			return (-1);
	}
	else 
		;
	return (0);
}

uint32_t get_load_command_num(t_infile *infile)
{
	uint32_t		 	n_lcmds;
	
	n_lcmds = 0;
	if (infile->type == IS_32)
		n_lcmds = ((struct mach_header *)infile->mac_header)->ncmds;
	if (infile->type == IS_64)
		n_lcmds = ((struct mach_header_64 *)infile->mac_header)->ncmds;
	if (infile->type == IS_BE)
		n_lcmds = reverse_32(1,
				((struct mach_header *)infile->mac_header)->ncmds);
	if (infile->type == IS_BE_64)
	{
		n_lcmds = reverse_32(1,
				((struct mach_header *)infile->mac_header)->ncmds);
	}
	return (n_lcmds);
}

int	iter_load_command(t_infile *infile)
{
	uint32_t		 	n_lcmds;
	void				*lc;
	uint32_t			cmdsize;

	lc = NULL;
	n_lcmds = get_load_command_num(infile);
	lc = (struct load_command *)infile->current;
	while (n_lcmds)
	{
		cmdsize = reverse_32(
			infile->type == IS_BE || infile->type == IS_BE_64,
			 ((struct load_command *)lc)->cmdsize);
		if (parse_load_command(infile, (struct load_command *)lc) < 0)
			return (error_gen("corrupted load commands"));
		if ((void *)lc + sizeof(uint32_t) > (void *)infile->start + infile->sz)
			return (error_gen("corrupted load commands"));
		lc = (void *)lc + cmdsize;
		n_lcmds--;
	}
	return (0);
}
