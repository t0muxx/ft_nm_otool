/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:13:38 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/31 09:13:30 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/* Si cpusubtype == X86_64 then on print only that sans mette l'arch*/

void	fat_print_arch(t_infile *file, cpu_type_t cputype, cpu_subtype_t cpusubtype)
{
	cputype = reverse_32(1, cputype);
	cpusubtype = reverse_32(1, cpusubtype);
	if (cputype == CPU_TYPE_I386)
		ft_printf("\n%s (for architecture i386):\n", file->filename);
	else if (cputype == CPU_TYPE_POWERPC)
		ft_printf("\n%s (for architecture ppc):\n", file->filename);
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
		fat_print_arch(file, fat_arch->cputype, fat_arch->cpusubtype);
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
		fat_print_arch(file, fat_arch->cputype, fat_arch->cpusubtype);
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

int	search_cputype_x64(t_infile *file, unsigned long magic_bytes)
{
	struct fat_header	*fat_header;
	uint32_t			i;
	uint64_t			offset;
	void				*fat_arch;

	i = 0;
	fat_header = file->start;
	fat_arch = file->start + sizeof(struct fat_header);
	while (i < reverse_32(1, fat_header->nfat_arch))
	{
		if (magic_bytes == FAT_MAGIC || magic_bytes == FAT_CIGAM)
			offset = reverse_32(1, ((struct fat_arch *)fat_arch)->offset);
		else if (magic_bytes == FAT_MAGIC_64 || magic_bytes == FAT_CIGAM_64)
			offset = reverse_64(1, ((struct fat_arch_64 *)fat_arch)->offset);
		if (reverse_32(1, ((struct fat_arch *)fat_arch)->cputype) == CPU_TYPE_X86_64)
		{
			file->start = (void *)file->start + offset;
			return (1);
		}
		if (magic_bytes == FAT_MAGIC || magic_bytes == FAT_CIGAM)
			fat_arch = (void *)fat_arch + sizeof(struct fat_arch);
		else if (magic_bytes == FAT_MAGIC_64 || magic_bytes == FAT_CIGAM_64)
			fat_arch = (void *)fat_arch + sizeof(struct fat_arch_64);
		i++;
	}
	return (0);
}

int	process_fat(t_infile *file)
{
	unsigned long	magic_bytes;

	magic_bytes = 0;
	if ((void *)file->start + sizeof(unsigned long)
			> (void *)file->start + file->sz)
		return (error_gen("corrupted fat header"));
	magic_bytes = *(uint32_t *)file->start;
	if (magic_bytes != FAT_MAGIC && magic_bytes != FAT_MAGIC_64 && magic_bytes != FAT_CIGAM && magic_bytes != FAT_CIGAM_64)
		return (process_macho(file));
	if ((void *)file->start + sizeof(struct fat_header) + sizeof(cpu_type_t)
	 > (void *)file->start + file->sz)
		return (error_gen("corrupted fat header"));
	if (search_cputype_x64(file, magic_bytes) > 0)
		return (process_macho(file));
	if (magic_bytes == FAT_MAGIC || magic_bytes == FAT_CIGAM)
		return (process_fat_32(file));
	if (magic_bytes == FAT_MAGIC_64 || magic_bytes == FAT_CIGAM_64)
		return (process_fat_64(file));
	return (0);
}
