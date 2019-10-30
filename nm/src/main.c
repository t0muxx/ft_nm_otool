/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:46:47 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/30 12:21:39 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int	process_args(char *file)
{
	t_infile *infile;

	infile = NULL;
	if (!(infile = process_infile(file)))
	{
		return (-1);
	}
	if (process_header(infile) < 0)
	{
		munmap(infile->start, infile->sz);
		free(infile);
		return (-1);
	}
	if (iter_load_command(infile) < 0)
	{
		munmap(infile->start, infile->sz);
		lst_section_free(infile->sections);
		lst_symbol_free(infile->symbols);
		free(infile);
		return (-1);
	}
	symbol_resolve(infile);
	if (infile->type == IS_32 || infile->type == IS_BE)
		lst_symbol_print_32(infile->symbols);
	else if (infile->type == IS_64 || infile->type == IS_BE_64)
		lst_symbol_print_64(infile->symbols);
	lst_symbol_free(infile->symbols);
	lst_section_free(infile->sections);
	munmap(infile->start, infile->sz);
	free(infile);
	return (0);
}

int	main(int argc, char **argv)
{
	int i;

	i = 1;
	if (argc == 1)
		process_args("./a.out");
	else
	{
		while (i < argc)
		{
			process_args(argv[i]);
			i++;
		}
	}
	return (0);
}
