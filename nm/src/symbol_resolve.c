/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_resolve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 08:46:56 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/25 16:22:01 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	symbol_resolve_sect(t_infile *file, uint8_t n_sect)
{
	int			i;
	t_section	*sections;
	char		*sect_name;

	sect_name = NULL;
	i = 0;
	sections = file->sections;
	while (sections != NULL && ++i < n_sect)
		sections = sections->next;
	if ((file->type == IS_32 || file->type == IS_BE) && sections != NULL)
		sect_name = ((struct section *)sections->section)->sectname;
	if ((file->type == IS_64 || file->type == IS_BE_64) && sections != NULL)
		sect_name = ((struct section_64 *)sections->section)->sectname;
	if (!sect_name)
		return ('?');
	if (!ft_strcmp(sect_name, SECT_TEXT))
		return ('T');
	if (!ft_strcmp(sect_name, SECT_DATA))
		return ('D');
	if (!ft_strcmp(sect_name, SECT_BSS))
		return ('B');
	return ('S');
}

char	symbol_get_letter(t_infile *file, uint8_t n_type, uint8_t n_sect, uint64_t n_value)
{
	char  c;
	uint8_t type;

	n_type = reverse_8(file->type == IS_BE || file->type == IS_BE_64, n_type);
	n_sect = reverse_8(file->type == IS_BE || file->type == IS_BE_64, n_sect);
	type = n_type & N_TYPE;
	c = '?';
	if (n_type & N_STAB)
		return ('-');
	else if (type == N_UNDF || type == N_PBUD)
	{
		c = 'U';
		if (type == N_UNDF && n_value > 0)
			c = 'C';
	}
	else if (type == N_ABS)
		c = 'A';
	else if (type == N_SECT)
		c = symbol_resolve_sect(file, n_sect);
	else if (type == N_INDR)
		c = 'I';
	if (!(n_type & N_EXT) && (c != '?'))
		c = ft_tolower(c);
	return (c);
}

void	symbol_resolve(t_infile *infile)
{
	t_symbol *tmp;

	tmp = infile->symbols;
	while (tmp)
	{
		if (infile->type == IS_32 || infile->type == IS_BE)
		{
			tmp->symb_char = symbol_get_letter(infile,
				((struct nlist *)tmp->symbol)->n_type, 
				((struct nlist *)tmp->symbol)->n_sect,
				tmp->symb_value);
		}
		if (infile->type == IS_64 || infile->type == IS_BE_64)
		{
			tmp->symb_char = symbol_get_letter(infile,
				((struct nlist_64 *)tmp->symbol)->n_type, 
				((struct nlist_64 *)tmp->symbol)->n_sect,
				tmp->symb_value);
		}
		tmp = tmp->next;
	}
}
