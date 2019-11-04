/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:48:28 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/04 15:49:30 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"


int	search_cputype_x64_work_off_ar_sz(t_infile *file, unsigned long magic_bytes,
		void *fat_arch, uint64_t *offset_arsz)
{
	if (magic_bytes == FAT_MAGIC || magic_bytes == FAT_CIGAM)
	{
		if (protect(file, (void *)fat_arch + sizeof(struct fat_arch)) < 0)
			return (error_gen("corrupted far_arch"));
		offset_arsz[0] = reverse_32(1, ((struct fat_arch *)fat_arch)->offset);
		offset_arsz[1] = reverse_32(1, ((struct fat_arch *)fat_arch)->size);
	}
	else if (magic_bytes == FAT_MAGIC_64 || magic_bytes == FAT_CIGAM_64)
	{
		if (protect(file, (void *)fat_arch + sizeof(struct fat_arch_64)) < 0)
			return (error_gen("corrupted far_arch"));
		offset_arsz[0] = reverse_64(1, ((struct fat_arch_64 *)fat_arch)->offset);
		offset_arsz[1] = reverse_64(1, ((struct fat_arch_64 *)fat_arch)->size);
	}
	return (0);
}

int	search_cputype_x64_work(t_infile *file, unsigned long magic_bytes,
		void *fat_arch)
{
	uint64_t			offset_arsz[2];
	
	offset_arsz[0] = 0;	
	offset_arsz[1] = 0;
	if (search_cputype_x64_work_off_ar_sz(file, magic_bytes,
	fat_arch, offset_arsz) < 0)
		return (-1);	
	if (offset_arsz[0] <= 0)
		return (error_gen("fat offset <= 0"));
	if (reverse_32(1, ((struct fat_arch *)fat_arch)->cputype) == CPU_TYPE_X86_64)
	{
		file->ar_sz = offset_arsz[1];
		file->start = (void *)file->start + offset_arsz[0];
		return (1);
	}
	return (0);
}


int	search_cputype_x64(t_infile *file, unsigned long magic_bytes)
{
	struct fat_header	*fat_header;
	uint32_t			i;
	void				*fat_arch;
	int					ret;

	ret = 0;
	i = 0;
	fat_header = file->start;
	fat_arch = file->start + sizeof(struct fat_header);
	while (i < reverse_32(1, fat_header->nfat_arch))
	{
		if ((ret = search_cputype_x64_work(file, magic_bytes, fat_arch)) < 0)
			return (-1);
		else if (ret == 1)
			return (1);
		if (magic_bytes == FAT_MAGIC || magic_bytes == FAT_CIGAM)
			fat_arch = (void *)fat_arch + sizeof(struct fat_arch);
		else if (magic_bytes == FAT_MAGIC_64 || magic_bytes == FAT_CIGAM_64)
			fat_arch = (void *)fat_arch + sizeof(struct fat_arch_64);
		i++;
	}
	return (0);
}
