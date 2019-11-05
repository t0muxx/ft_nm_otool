/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:13:38 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/05 10:30:41 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int	process_fat_64_work(t_infile *file, void *save_start,
		struct fat_arch_64 *fat_arch, int i)
{
	if ((void *)save_start + reverse_64(1, fat_arch[i].offset)
	> (void *)save_start + file->sz || (void *)save_start
	+ reverse_64(1, fat_arch[i].offset)
	+ reverse_64(1, fat_arch[i].size) > (void *)save_start + file->sz)
		return (error_gen("corrupted fat arch"));
	if (reverse_64(1, fat_arch[i].offset) <= 0)
		return (error_gen("fat offset <= 0"));
	file->start = (void *)file->start + reverse_64(1, fat_arch[i].offset);
	fat_print_arch(file, fat_arch[i].cputype, fat_arch[i].cpusubtype);
	process_macho(file);
	return (0);
}

int	process_fat_64(t_infile *file)
{
	struct fat_arch_64	*fat_arch;
	struct fat_header	*fat_head;
	uint32_t			i;
	void				*save_start;

	save_start = file->start;
	i = 0;
	if ((void *)file->start + sizeof(struct fat_header)
	+ sizeof(struct fat_arch_64)
		> (void *)file->start + file->sz)
		return (error_gen("corrupted fat header"));
	fat_arch = file->start + sizeof(struct fat_header);
	fat_head = file->start;
	while (i < reverse_32(1, fat_head->nfat_arch))
	{
		if (process_fat_64_work(file, save_start, fat_arch, i) < 0)
			return (-1);
		file->start = save_start;
		if ((void *)fat_arch + sizeof(struct fat_arch_64)
		> (void *)file->save + file->sz)
			return (error_gen("corrupted fat arch"));
		i++;
	}
	return (0);
}

int	process_fat_32_work(t_infile *file, void *save_start,
			struct fat_arch *fat_arch, int i)
{
	if ((void *)save_start + reverse_32(1, fat_arch[i].offset)
	> (void *)save_start + file->sz || (void *)save_start
	+ reverse_32(1, fat_arch[i].offset)
	+ reverse_32(1, fat_arch[i].size) > (void *)save_start + file->sz)
		return (error_gen("corrupted fat arch"));
	if (reverse_32(1, fat_arch[i].offset) <= 0)
		return (error_gen("fat offset <= 0"));
	file->start = (void *)file->start + reverse_32(1, fat_arch[i].offset);
	fat_print_arch(file, fat_arch[i].cputype, fat_arch[i].cpusubtype);
	process_macho(file);
	return (0);
}

int	process_fat_32(t_infile *file)
{
	struct fat_arch		*fat_arch;
	struct fat_header	*fat_head;
	uint32_t			i;
	void				*save_start;

	save_start = file->start;
//	ft_putstr("process_fat\n");
	i = 0;
	if (protect(file, (void *)file->start
		+ sizeof(struct fat_header) + sizeof(struct fat_arch)) < 0)
		return (error_gen("corrupted fat header"));
	fat_arch = file->start + sizeof(struct fat_header);
	fat_head = file->start;
	while (i < reverse_32(1, fat_head->nfat_arch))
	{
		if (process_fat_32_work(file, save_start, fat_arch, i) < 0)
			return (-1);
		file->start = save_start;
		if ((void *)fat_arch + sizeof(struct fat_arch)
		> (void *)file->save + file->sz)
			return (error_gen("corrupted fat arch"));
		i++;
	}
	return (0);
}

int	process_fat(t_infile *file)
{
	unsigned long	magic_bytes;

	magic_bytes = 0;
	if (protect(file, (void *)file->start + sizeof(unsigned long)) < 0)
		return (error_gen("corrupted fat header"));
	magic_bytes = *(uint32_t *)file->start;
	if (magic_bytes != FAT_MAGIC && magic_bytes != FAT_MAGIC_64
	&& magic_bytes != FAT_CIGAM && magic_bytes != FAT_CIGAM_64)
		return (1);
	if (protect(file, (void *)file->start
	+ sizeof(struct fat_header) + sizeof(cpu_type_t)) < 0)
		return (error_gen("corrupted fat header"));
	if (search_cputype_x64(file, magic_bytes) > 0)
		return (process_macho(file));
	if (magic_bytes == FAT_MAGIC || magic_bytes == FAT_CIGAM)
		return (process_fat_32(file));
	if (magic_bytes == FAT_MAGIC_64 || magic_bytes == FAT_CIGAM_64)
		return (process_fat_64(file));
	return (1);
}
