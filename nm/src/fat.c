/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:13:38 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/30 16:50:02 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	fat_print_arch(t_infile *file, cpu_type_t cputype)
{
	cputype = reverse_32(1, cputype);
	if (cputype == CPU_TYPE_X86)
		ft_printf("\n%s (for architecture i386):\n", file->filename);
	else if (cputype == CPU_TYPE_X86_64)
		ft_printf("\n%s (for architecture x86_64):\n", file->filename);
}

int	process_fat_64(t_infile *file)
{
	struct fat_arch_64	*fat_arch;
	struct fat_header	*fat_head;
	uint32_t			i;
	void				*save_start;

	save_start = file->start;
	i = 0;
	if ((void *)file->start + sizeof(struct fat_header) + sizeof(struct fat_arch_64)
		> (void *)file->start + file->sz )
		return (error_gen("corrupted fat header"));
	fat_arch = file->start + sizeof(struct fat_header);
	fat_head = file->start;
	while (i < reverse_32(1, fat_head->nfat_arch))
	{
		if ((void *)save_start + reverse_64(1, fat_arch->offset)
		> (void *)save_start + file->sz || (void *)save_start 
		+ reverse_64(1, fat_arch->offset) 
		+ reverse_64(1,fat_arch->size) > (void *)save_start + file->sz )
			return (error_gen("corrupted fat arch"));
		file->start += reverse_64(1, fat_arch->offset);
		fat_print_arch(file, fat_arch->cputype);
		process_header(file);
		file->start = save_start;
		if ((void *)fat_arch + sizeof(fat_arch)
		> (void *)file->start + file->sz)
			return (error_gen("corrupted fat arch"));
		i++;
		fat_arch = fat_arch + i;
	}
	return (0);
}

int	process_fat_32(t_infile *file)
{
	struct fat_arch		*fat_arch;
	struct fat_header	*fat_head;
	uint32_t			i;
	void				*save_start;

	save_start = file->start;
	i = 0;
	if ((void *)file->start + sizeof(struct fat_header) + sizeof(struct fat_arch)
		> (void *)file->start + file->sz )
		return (error_gen("corrupted fat header"));
	fat_arch = file->start + sizeof(struct fat_header);
	fat_head = file->start;
	while (i < reverse_32(1, fat_head->nfat_arch))
	{
		if ((void *)save_start + reverse_32(1, fat_arch->offset)
		> (void *)save_start + file->sz || (void *)save_start 
		+ reverse_32(1, fat_arch->offset) 
		+ reverse_32(1,fat_arch->size) > (void *)save_start + file->sz )
			return (error_gen("corrupted fat arch"));
		file->start = (void *)file->start + reverse_32(1, fat_arch->offset);
		fat_print_arch(file, fat_arch->cputype);
		process_macho(file);
		file->start = save_start;
		if ((void *)fat_arch + sizeof(fat_arch)
		> (void *)file->start + file->sz)
			return (error_gen("corrupted fat arch"));
		i++;
		fat_arch = fat_arch + i;
	}
	return (0);
}

int	process_fat(t_infile *file)
{
	unsigned long magic_bytes;

	magic_bytes = 0;
	if ((void *)file->start + sizeof(unsigned long)
			> (void *)file->start + file->sz)
		return (error_gen("corrupted fat header"));
	magic_bytes = *(uint32_t *)file->start;
	if (magic_bytes != FAT_MAGIC && magic_bytes != FAT_MAGIC_64 && magic_bytes != FAT_CIGAM && magic_bytes != FAT_CIGAM_64)
		return (process_macho(file));
	if (magic_bytes == FAT_MAGIC || magic_bytes == FAT_CIGAM)
		return (process_fat_32(file));
	if (magic_bytes == FAT_MAGIC_64 || magic_bytes == FAT_CIGAM_64)
		return (process_fat_64(file));
	return (0);
}
