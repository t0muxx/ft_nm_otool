/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:13:38 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/04 12:47:18 by tmaraval         ###   ########.fr       */
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
		ft_printf("\n%s (for architecture ):\n", file->filename);
	else if (cputype == CPU_TYPE_X86_64)
		ft_printf("\n%s (for architecture x86_64):\n", file->filename);
	else if (cputype == CPU_TYPE_ARM64)
		ft_printf("\n%s (for architecture arm64):\n", file->filename);
	else if (cputype == CPU_TYPE_ARM)
	{
		if (cpusubtype == CPU_SUBTYPE_ARM_V7)
			ft_printf("\n%s (for architecture armv7):\n", file->filename);
		else if (cpusubtype == CPU_SUBTYPE_ARM_V7S)
			ft_printf("\n%s (for architecture armv7s):\n", file->filename);
	}
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
		return (error_gen("corrupted fat header 5 "));
	fat_arch = file->start + sizeof(struct fat_header);
	fat_head = file->start;
	while (i < reverse_32(1, fat_head->nfat_arch))
	{
		if ((void *)save_start + reverse_64(1, fat_arch[i].offset)
		> (void *)save_start + file->sz || (void *)save_start 
		+ reverse_64(1, fat_arch[i].offset) 
		+ reverse_64(1,fat_arch[i].size) > (void *)save_start + file->sz )
			return (error_gen("corrupted fat arch 6"));
		if (reverse_64(1, fat_arch[i].offset) <= 0)
			return (error_gen("fat offset <= 0"));
		file->start = (void *)file->start + reverse_64(1, fat_arch[i].offset);
		fat_print_arch(file, fat_arch[i].cputype, fat_arch[i].cpusubtype);
		process_macho(file);
		file->start = save_start;
		if ((void *)fat_arch + sizeof(struct fat_arch_64)
		> (void *)file->save + file->sz)
			return (error_gen("corrupted fat arch 7"));
		i++;
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
		return (error_gen("corrupted fat header 3"));
	fat_arch = file->start + sizeof(struct fat_header);
	fat_head = file->start;
	while (i < reverse_32(1, fat_head->nfat_arch))
	{
		if ((void *)save_start + reverse_32(1, fat_arch[i].offset)
		> (void *)save_start + file->sz || (void *)save_start 
		+ reverse_32(1, fat_arch[i].offset) 
		+ reverse_32(1,fat_arch[i].size) > (void *)save_start + file->sz )
			return (error_gen("corrupted fat arch 4"));
//		printf("offset == %u\n", reverse_32(1, fat_arch[i].offset));
		if (reverse_32(1, fat_arch[i].offset) <= 0)
			return (error_gen("fat offset <= 0"));
		file->start = (void *)file->start + reverse_32(1, fat_arch[i].offset);
		fat_print_arch(file, fat_arch[i].cputype, fat_arch[i].cpusubtype);
		process_macho(file);
		file->start = save_start;
		if ((void *)fat_arch + sizeof(struct fat_arch_64)
		> (void *)file->save + file->sz)
			return (error_gen("corrupted fat arch 5"));
		i++;
	}
	return (0);
}

int	search_cputype_x64(t_infile *file, unsigned long magic_bytes)
{
	struct fat_header	*fat_header;
	uint32_t			i;
	uint64_t			offset;
	void				*fat_arch;
	uint64_t			ar_sz;

	ar_sz = 0;
	i = 0;
	fat_header = file->start;
	fat_arch = file->start + sizeof(struct fat_header);
	while (i < reverse_32(1, fat_header->nfat_arch))
	{
		if (magic_bytes == FAT_MAGIC || magic_bytes == FAT_CIGAM)
		{
			if ((void *)fat_arch + sizeof(struct fat_arch) > (void *)file->start + file->sz)
				return (error_gen("corrupted far_arch"));
			offset = reverse_32(1, ((struct fat_arch *)fat_arch)->offset);
			ar_sz = reverse_32(1, ((struct fat_arch *)fat_arch)->size);
		}
		else if (magic_bytes == FAT_MAGIC_64 || magic_bytes == FAT_CIGAM_64)
		{
			if ((void *)fat_arch + sizeof(struct fat_arch_64) > (void *)file->start + file->sz)
				return (error_gen("corrupted far_arch"));
			offset = reverse_64(1, ((struct fat_arch_64 *)fat_arch)->offset);
			ar_sz = reverse_64(1, ((struct fat_arch_64 *)fat_arch)->size);
		}
		if (offset <= 0)
			return(error_gen("fat offset <= 0"));
		if (reverse_32(1, ((struct fat_arch *)fat_arch)->cputype) == CPU_TYPE_X86_64)
		{
			file->ar_sz = ar_sz;
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
//	ft_putstr("process_fat : \n");
	if ((void *)file->start + sizeof(unsigned long)
			> (void *)file->start + file->sz)
		return (error_gen("corrupted fat header 0"));
	magic_bytes = *(uint32_t *)file->start;
//	printf("magic_bytes == %lx\n", magic_bytes);
	if (magic_bytes != FAT_MAGIC && magic_bytes != FAT_MAGIC_64 && magic_bytes != FAT_CIGAM && magic_bytes != FAT_CIGAM_64)
		return (1);
	if ((void *)file->start + sizeof(struct fat_header) + sizeof(cpu_type_t)
	 > (void *)file->start + file->sz)
		return (error_gen("corrupted fat header 1"));
	if (search_cputype_x64(file, magic_bytes) > 0)
	{
//		ft_putstr("found x64\n");
		return (process_macho(file));
	}
	if (magic_bytes == FAT_MAGIC || magic_bytes == FAT_CIGAM)
		return (process_fat_32(file));
	if (magic_bytes == FAT_MAGIC_64 || magic_bytes == FAT_CIGAM_64)
		return (process_fat_64(file));
	return (1);
}
