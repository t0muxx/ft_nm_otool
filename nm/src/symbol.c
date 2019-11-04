/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:48:07 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/04 15:00:23 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

size_t	protected_strlen(char *str, t_infile *file)
{
	size_t i;

	i = 0;
	while (((void *)str + i < (void *)file->save + file->sz) && str[i])
		i++;
	return (i);
}

void	parse_symtab_add_sym(t_infile *file, void *sym, 
		void *strtab, uint32_t	strsize)
{
	char		*sym_name;
	uint64_t	sym_value;

	if (file->type == IS_32 || file->type == IS_BE)
	{
		sym_name = strtab + reverse_32(
			file->type == IS_BE, ((struct nlist *)sym)->n_un.n_strx);
		sym_value = reverse_32(file->type == IS_BE, ((struct nlist *)sym)->n_value);
	}
	if (file->type == IS_64 || file->type == IS_BE_64)
	{
		sym_name = strtab + reverse_32(
			file->type == IS_BE_64, ((struct nlist_64 *)sym)->n_un.n_strx);
		sym_value = reverse_64(file->type == IS_BE_64, ((struct nlist_64 *)sym)->n_value);
	}
	if ((void *)sym_name > (void *)file->save + file->sz 
		|| (void *)sym_name > (void *)strtab + strsize)
	{
		sym_name = "bad string index";
		lst_symbol_append_nosort(&file->symbols, 
		lst_symbol_new(sym, sym_name, protected_strlen(sym_name, file),sym_value));
		return;
	}
	lst_symbol_append_nosort(&file->symbols, 
	lst_symbol_new(sym, sym_name, protected_strlen(sym_name, file),sym_value));

}

void	parse_symtab_iter_64(t_infile *file, void *sym_data_start, uint32_t nsymb, void *strtab)
{
	uint32_t i;
	struct nlist_64 *sym_data;
	uint32_t strsize;

	sym_data = (struct nlist_64 *)sym_data_start;	
	i = 0;
	strsize = reverse_32(file->type == IS_BE_64, file->symtab_command->strsize);
	while (i < nsymb)
	{
		if (!((void *)(struct nlist_64 *)(sym_data + i)
			> (void *)file->save + file->sz)
		&& !(sym_data[i].n_type & N_STAB))
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

void	parse_symtab_iter_32(t_infile *file, void *sym_data_start, uint32_t nsymb, void *strtab)
{
	uint32_t i;
	struct nlist *sym_data;
	uint32_t strsize;

	i = 0;
	sym_data = (struct nlist *)sym_data_start;
	strsize = reverse_32(file->type == IS_BE, file->symtab_command->strsize);
//	printf("strzie = %u strtab : %p sym_data : %p\n", strsize, strtab, sym_data);
	while (i < nsymb)
	{
		if (!((void *)(struct nlist *)(sym_data + i)
				> (void *)file->save + file->sz))
		{
//			printf("n_type = %#x\n", sym_data[i].n_type);
			if (!(sym_data[i].n_type & N_STAB))
			{
				parse_symtab_add_sym(
					file, (struct nlist *)sym_data + i, strtab, strsize);
			}
		}
			i++;
	}
}

int	parse_symtab(t_infile *file, struct symtab_command *st)
{
	void			*strtab;
	uint32_t		nsymb;

	if (protect(file, (void *)st + sizeof(struct symtab_command)) < 0)
		return (0);
	file->symtab_command = st;
	strtab = (void *)file->start + reverse_32(
			file->type == IS_BE || file->type == IS_BE_64, st->stroff);
	nsymb = reverse_32(file->type == IS_BE || file->type == IS_BE_64,st->nsyms);
	if (protect(file, (void *) file->start
	+ reverse_32(file->type == IS_BE || file->type == IS_BE_64, st->stroff)
	+ reverse_32(file->type == IS_BE || file->type == IS_BE_64, st->strsize))
	> 0)
		return (-1);
	if (file->type == IS_32 || file->type == IS_BE)
		parse_symtab_iter_32(file, (void *)file->start + reverse_32(file->type == IS_BE, st->symoff), nsymb, strtab);
	if (file->type == IS_64 || file->type == IS_BE_64)
		parse_symtab_iter_64(file, (void *)file->start + reverse_32(file->type == IS_BE_64, st->symoff), nsymb, strtab);
	return (0);
}
