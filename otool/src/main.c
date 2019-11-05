/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:46:47 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/05 16:18:27 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

/* TODO : MULTI ARGS
 * moar tests
 * nm-otool-test/binary/ls_string_table_corr5 /!\
 * ppr or not ? nm-otool-test/fat/audiodevice
 * to check nm-otool-test/lib/libswiftCore.dylib.out
 * */

int	process_normal(t_infile *infile)
{
//	ft_putstr("process_normal\n");
	if (process_header(infile) < 0)
		return (error_gen("corrupted fat header"));
	if (iter_load_command(infile) < 0)
	{
		return (-1);
	}
	// here we print our text
	print_text(infile);
	return (0);
}

int	process_macho(t_infile *infile)
{
	int (*func_array[3])(t_infile *file);
	int ret;
	int i;

	i = 0;
	ret = 0;
//	ft_putstr("process_macho\n");
	func_array[0] = process_archive;
	func_array[1] = process_fat;
	func_array[2] = process_normal;
	while (i < 3)
	{
		ret = (*func_array[i])(infile);
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
	t_infile	*infile;
	int			ret;

	ret = 0;
	infile = NULL;
	if (!(infile = process_infile(file)))
		return (-1);
	process_macho(infile);
	protected_free(infile);
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
			if (argc > 2)
				ft_printf("\n%s:\n", argv[i]);
			process_args(argv[i]);
			i++;
		}
	}
	return (0);
}