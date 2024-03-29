/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:48:07 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/04 16:52:44 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	*parse_symtab_name_value(t_infile *file, void *sym, void *strtab,
		uint64_t *sym_value)
{
	char		*sym_name;

	if (file->type == IS_32 || file->type == IS_BE)
	{
		sym_name = strtab + reverse_32(
			file->type == IS_BE, ((struct nlist *)sym)->n_un.n_strx);
		*sym_value = reverse_32(file->type == IS_BE,
				((struct nlist *)sym)->n_value);
	}
	if (file->type == IS_64 || file->type == IS_BE_64)
	{
		sym_name = strtab + reverse_32(
			file->type == IS_BE_64, ((struct nlist_64 *)sym)->n_un.n_strx);
		*sym_value = reverse_64(file->type == IS_BE_64,
				((struct nlist_64 *)sym)->n_value);
	}
	return (sym_name);
}

void	parse_symtab_add_sym(t_infile *file, void *sym,
		void *strtab, uint32_t strsize)
{
	uint64_t	sym_value;
	char		*sym_name;

	sym_name = parse_symtab_name_value(file, sym, strtab, &sym_value);
	if (protect(file, (void *)sym_name) < 0
		|| (void *)sym_name > (void *)strtab + strsize)
	{
		sym_name = "bad string index";
		lst_symbol_append_nosort(&file->symbols,
		lst_symbol_new(sym, sym_name,
			protected_strlen(sym_name, file), sym_value));
		return ;
	}
	lst_symbol_append_nosort(&file->symbols, lst_symbol_new(sym, sym_name,
			protected_strlen(sym_name, file), sym_value));
}

void	parse_symtab_iter_64(t_infile *file, void *sym_data_start,
		uint32_t nsymb, void *strtab)
{
	uint32_t		i;
	struct nlist_64	*sym_data;
	uint32_t		strsize;

	sym_data = (struct nlist_64 *)sym_data_start;
	i = 0;
	strsize = reverse_32(file->type == IS_BE_64, file->symtab_command->strsize);
	while (i < nsymb)
	{
		if (protect(file, (void *)(struct nlist_64 *)(sym_data + i)) == 0)
		{
			if (!(sym_data[i].n_type & N_STAB))
			{
				parse_symtab_add_sym(
					file, (struct nlist_64 *)sym_data + i, strtab, strsize);
			}
		}
		i++;
	}
}

void	parse_symtab_iter_32(t_infile *file, void *sym_data_start,
		uint32_t nsymb, void *strtab)
{
	uint32_t		i;
	struct nlist	*sym_data;
	uint32_t		strsize;

	i = 0;
	sym_data = (struct nlist *)sym_data_start;
	strsize = reverse_32(file->type == IS_BE, file->symtab_command->strsize);
	while (i < nsymb)
	{
		if (protect(file, (void *)(struct nlist *)(sym_data + i)) == 0)
		{
			if (!(sym_data[i].n_type & N_STAB))
			{
				parse_symtab_add_sym(
					file, (struct nlist *)sym_data + i, strtab, strsize);
			}
		}
		i++;
	}
}

int		parse_symtab(t_infile *file, struct symtab_command *st)
{
	void			*strtab;
	uint32_t		nsym;

	if (protect(file, (void *)st + sizeof(struct symtab_command)) < 0)
		return (0);
	file->symtab_command = st;
	strtab = (void *)file->start + reverse_32(
			file->type == IS_BE || file->type == IS_BE_64, st->stroff);
	nsym = reverse_32(file->type == IS_BE || file->type == IS_BE_64, st->nsyms);
	if (protect(file, (void *)file->start
	+ reverse_32(file->type == IS_BE || file->type == IS_BE_64, st->stroff)
	+ reverse_32(file->type == IS_BE || file->type == IS_BE_64, st->strsize))
	> 0)
		return (-1);
	if (file->type == IS_32 || file->type == IS_BE)
	{
		parse_symtab_iter_32(file, (void *)file->start
			+ reverse_32(file->type == IS_BE, st->symoff), nsym, strtab);
	}
	if (file->type == IS_64 || file->type == IS_BE_64)
	{
		parse_symtab_iter_64(file, (void *)file->start
			+ reverse_32(file->type == IS_BE_64, st->symoff), nsym, strtab);
	}
	return (0);
}
