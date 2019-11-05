/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:10:27 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/05 17:12:24 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	print_file_type(t_infile *file, char *type)
{
	if (file->type_printed == 0)
	{
		ft_printf("%s : %s\n", type, file->filename);
		file->type_printed = 1;
	}
}

int		print_text_bytes(t_infile *file, uint8_t *current, uint32_t print)
{
	int		i;
	uint8_t *byte;
	int		nb;
	char	base[16];

	nb = 0;
	ft_strcpy(base, "0123456789abcdef")	;
	i = 0;
	byte = current;
	while (i < 16 && print)
	{
		nb = reverse_8(file->type == IS_BE || file->type == IS_BE_64, 
				*byte) / 16;
		ft_putchar(base[nb]);
		nb = reverse_8(file->type == IS_BE || file->type == IS_BE_64, 
				*byte) % 16;
		ft_putchar(base[nb]);
		ft_putstr(" ");
		i++;
		byte++;
		print--;
		if (protect(file, (void *)byte) < 0)
			return (-1);
	}
	return (0);
}

void	print_text_32(t_infile *file)
{
	uint8_t *current;
	uint64_t		i;
	uint32_t		print;

	i = 0;
	current = (uint8_t *)file->save + file->text_offs;
	ft_putstr("(__TEXT,__text) section\n");
	while (file->text_sz > 0)
	{
		print = 16;
		ft_printf("%08lx\t", file->text_addr);
		if (file->text_sz - i < 16)
			print = file->text_sz - i;
		if (print_text_bytes(file, current, print) < 0)
			return ;
		i += 16;
		current = (void *)current + 16;
		file->text_addr += 16;
		ft_putendl("");
		if (protect(file, (void *)current) < 0)
			return ;
	}
}

void	print_text_64(t_infile *file)
{
	uint8_t			*current;
	uint64_t		i;
	uint32_t		print;

	i = 0;
	current = (uint8_t *)file->save + file->text_offs;
	ft_putstr("(__TEXT,__text) section\n");
	while (i < file->text_sz)
	{
		print = 16;
		ft_printf("%016lx\t", file->text_addr);
		if (file->text_sz - i < 16)
			print = file->text_sz - i;
		if (print_text_bytes(file, current, print) < 0)
			return ;
		i += 16;
		current = (void *)current + 16;
		file->text_addr += 16;
		ft_putendl("");
		if (protect(file, (void *)current) < 0)
			return ;
	}

}

void	print_text(t_infile *file)
{
	if (file->type == IS_32 || file->type == IS_BE)
		print_text_32(file);
	if (file->type == IS_64 || file->type == IS_BE_64)
		print_text_64(file);
}
