/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:46:47 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/04 13:15:02 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/* TODO : MULTI ARGS
 * moar tests
 * nm-otool-test/binary/ls_string_table_corr5 /!\
 * ppr or not ? nm-otool-test/fat/audiodevice
 * to check nm-otool-test/lib/libswiftCore.dylib.out
 * */

int	process_normal(t_infile *infile)
{
//	ft_putstr("process_normal : \n");
	if (process_header(infile) < 0)
		return error_gen("corrupted fat header");
	if (iter_load_command(infile) < 0)
	{
		munmap(infile->start, infile->sz);
		lst_section_free(infile->sections);
		lst_symbol_free(infile->symbols);
		return (-1);
	}
	symbol_resolve(infile);
	if (infile->type == IS_32 || infile->type == IS_BE)
		lst_symbol_print_32(infile->symbols);
	else if (infile->type == IS_64 || infile->type == IS_BE_64)
		lst_symbol_print_64(infile->symbols);
	lst_symbol_free(infile->symbols);
	infile->symbols = NULL;
	lst_section_free(infile->sections);
	infile->sections = NULL;
	return (0);

}

int	process_macho(t_infile *infile)
{
//	ft_putstr("process_macho : \n");
	int (*func_array[3])(t_infile *file);
	int ret;
	int i;

	i = 0;
	ret = 0;
	func_array[0] = process_archive;
	func_array[1] = process_fat;
	func_array[2] = process_normal;
	while (i < 3)
	{
		ret = (*func_array[i])(infile);
	//	printf("ret == %d et i == %d\n", ret, i);
		if (ret < 0)
			return (-1);
		else if (ret == 0)
			return (0);
		i++;
	}
	return (0);
}

int	process_args(char *file)
{
	t_infile *infile;
	int		ret;

	ret = 0;
	infile = NULL;
	if (!(infile = process_infile(file)))
	{
		return (-1);
	}
	process_macho(infile);
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
