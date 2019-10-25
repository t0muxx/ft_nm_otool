/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:48:07 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/25 11:43:21 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

size_t	protected_strlen(char *str, t_infile *file)
{
	size_t i;

	i = 0;
	while (((void *)str + i < (void *)file->start + file->sz) && str[i])
		i++;
	return (i);
}

void	parse_symtab_iter_64(t_infile *file, void *sym_data_start, uint32_t nsymb, void *strtab)
{
	uint32_t i;
	struct nlist_64 *sym_data;
	char *sym_name;

	sym_data = (struct nlist_64 *)sym_data_start;	
	i = 0;
	while (i < nsymb)
	{
		if (!((void *)(struct nlist_64 *)(sym_data + i)
				> (void *)file->start + file->sz))
		{
			if (!(reverse_8(
					file->type == IS_BE_64, sym_data[i].n_type) & N_STAB))
			{
			sym_name = strtab + reverse_32(
					file->type == IS_BE_64, sym_data[i].n_un.n_strx);
			lst_symbol_append(&file->symbols,
				lst_symbol_new((struct nlist_64 *)sym_data + i,
					sym_name, protected_strlen(sym_name, file),
					reverse_64(file->type == IS_BE_64, sym_data[i].n_value)));
			}
			i++;
		}
	}
}

void	parse_symtab_iter_32(t_infile *file, void *sym_data_start, uint32_t nsymb, void *strtab)
{
	uint32_t i;
	struct nlist *sym_data;
	char *sym_name;

	i = 0;
	sym_data = (struct nlist *)sym_data_start;	
	while (i < nsymb)
	{
		if (!((void *)(struct nlist *)(sym_data + i)
				> (void *)file->start + file->sz))
		{
			if (!(reverse_8(file->type == IS_BE ,sym_data[i].n_type) & N_STAB))
			{
				sym_name = strtab + reverse_32(
						file->type == IS_BE, sym_data[i].n_un.n_strx);
				lst_symbol_append(&file->symbols,
					lst_symbol_new((struct nlist *)sym_data + i,
						sym_name, protected_strlen(sym_name, file),
						reverse_32(file->type == IS_BE, sym_data[i].n_value)));
			}
			i++;
		}
	}
}

void	parse_symtab(t_infile *file, struct symtab_command *st)
{
	void			*strtab;
	uint32_t		nsymb;

	if ((void *)st + sizeof(struct symtab_command) > (void *)file->start + file->sz)
		return ;
	strtab = (void *)file->start + reverse_32(
			file->type == IS_BE || file->type == IS_BE_64, st->stroff);
	nsymb = reverse_32(file->type == IS_BE || file->type == IS_BE_64,st->nsyms);
	if (file->type == IS_32 || file->type == IS_BE)
		parse_symtab_iter_32(file, (void *)file->start + st->symoff, nsymb, strtab);
	if (file->type == IS_64 || file->type == IS_BE_64)
		parse_symtab_iter_64(file, (void *)file->start + st->symoff, nsymb, strtab);
}
