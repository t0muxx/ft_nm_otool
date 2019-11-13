/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:10:27 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/13 08:16:02 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	print_text_32(t_infile *file)
{
	uint8_t			*current;
	uint64_t		i;
	uint32_t		print;

	i = 0;
	current = (uint8_t *)file->start + file->text_offs;
	ft_putstr("Contents of (__TEXT,__text) section\n");
	while (i < file->text_sz)
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
	current = (uint8_t *)file->start + file->text_offs;
	ft_putstr("Contents of (__TEXT,__text) section\n");
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

int		print_text_bytes_dword(t_infile *file, uint8_t *current, uint32_t print)
{
	uint64_t	i;
	uint32_t	nb;
	uint8_t		*byte;

	nb = 0;
	i = 0;
	byte = current;
	while (i < 16 && print)
	{
		if (file->cputype == CPU_TYPE_POWERPC)
			nb = reverse_32(1, *(uint32_t *)&byte[i]);
		else
			nb = *(uint32_t *)&byte[i];
		ft_printf("%08x ", nb);
		i += 4;
		print--;
		if (protect(file, (void *)current) < 0)
			return (-1);
	}
	return (0);
}

void	print_text_arm(t_infile *file)
{
	void			*current;
	uint32_t		i;
	uint32_t		print;

	i = 0;
	current = (void *)file->start + file->text_offs;
	ft_putstr("Contents of (__TEXT,__text) section\n");
	while (i < file->text_sz)
	{
		print = 4;
		if (file->cputype == CPU_TYPE_ARM64)
			ft_printf("%016lx\t", file->text_addr);
		else
			ft_printf("%08x\t", file->text_addr);
		if (file->text_sz - i < 16)
			print = (file->text_sz - i) / 4;
		if (print_text_bytes_dword(file, current, print) < 0)
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
	if (file->cputype == CPU_TYPE_I386)
		print_text_32(file);
	if (file->cputype == CPU_TYPE_X86_64)
		print_text_64(file);
	if (file->cputype == CPU_TYPE_ARM || file->cputype == CPU_TYPE_ARM64
	|| file->cputype == CPU_TYPE_POWERPC)
		print_text_arm(file);
}
