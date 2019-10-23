/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:55:10 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/23 16:15:23 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int	iter_load_command(t_infile *infile)
{
	uint32_t n_lcmds;

	if (infile->type == IS_32)
		n_lcmds = ((struct mach_header *)infile->mac_header)->ncmds;
	if (infile->type == IS_64)
		n_lcmds = ((struct mach_header_64 *)infile->mac_header)->ncmds;
	if (infile->type == IS_BE)
		n_lcmds = ((struct mach_header *)infile->mac_header)->ncmds;
	if (infile->type == IS_BE_64)
		n_lcmds = ((struct mach_header *)infile->mac_header)->ncmds;
	return (0);
}
