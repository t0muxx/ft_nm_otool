/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:55:10 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/24 16:35:37 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int	parse_load_command(t_infile *infile, struct load_command *lc)
{
	if ((void *)lc + sizeof(uint32_t) > (void *)infile->start + infile->sz)
		return (-1);
	// Need to reverse bits :
	if (lc->cmd == LC_SEGMENT || lc->cmd == LC_SEGMENT_64)
		parse_segment(infile, lc);
	else if (lc->cmd == LC_SYMTAB)
		parse_symtab(infile, (struct symtab_command *)lc);
	else 
		;
	return (0);
}

int	iter_load_command(t_infile *infile)
{
	uint32_t		 	n_lcmds;
	void				*lc;

	lc = NULL;
	if (infile->type == IS_32)
		n_lcmds = ((struct mach_header *)infile->mac_header)->ncmds;
	if (infile->type == IS_64)
		n_lcmds = ((struct mach_header_64 *)infile->mac_header)->ncmds;
	// Need to reverse bits :
	if (infile->type == IS_BE)
		n_lcmds = ((struct mach_header *)infile->mac_header)->ncmds;
	if (infile->type == IS_BE_64)
		n_lcmds = ((struct mach_header *)infile->mac_header)->ncmds;
	lc = (struct load_command *)infile->current;
	while (n_lcmds)
	{
		if (parse_load_command(infile, (struct load_command *)lc) < 0)
			return (error_gen("corrupted load commands"));
		if ((void *)lc + sizeof(uint32_t) > (void *)infile->start + infile->sz)
			return (error_gen("corrupted load commands"));
		lc = (void *)lc + ((struct load_command *)lc)->cmdsize;  
		n_lcmds--;
	}
	return (0);
}
