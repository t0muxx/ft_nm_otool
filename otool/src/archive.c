/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:41:54 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/14 14:47:06 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	archive_fw_symdef(t_infile *file, struct ar_hdr *ar_header)
{
	char	*name;
	int		ret;

	ret = 0;
	name = NULL;
	if (!ft_strncmp(ar_header->ar_name, AR_EFMT1, ft_strlen(AR_EFMT1)))
	{
		name = (char *)ar_header + sizeof(struct ar_hdr);
		ret = ft_atoi((char *)ar_header->ar_name + ft_strlen(AR_EFMT1));
		if (!ft_strncmp(name, SYMDEF, ret) ||
		!ft_strncmp(name, SYMDEF_SORTED, ret))
		{
			file->start = (void *)file->start +
				sizeof(struct ar_hdr) + ft_atoi(ar_header->ar_size);
		}
	}
}

int		parse_archive_member_work(t_infile *file, struct ar_hdr *ar_header)
{
	unsigned long	magic_bytes;
	int				offset;

	offset = 0;
	magic_bytes = 0;
	ar_header = file->start;
	if (protect(file, (void *)ar_header + sizeof(struct ar_hdr)) < 0)
		return (error_gen("malformed archive header"));
	if (ft_strncmp(ar_header->ar_fmag, "`\n", 2))
		return (error_gen("malformed archive header"));
	offset = get_str_offset_archive(file, ar_header);
	file->start = (void *)file->start + sizeof(struct ar_hdr) + offset;
	magic_bytes = *(uint32_t *)((void *)file->start);
	if (!(!ft_strncmp((char *)file->start, ARMAG, SARMAG)
	|| magic_bytes == FAT_MAGIC || magic_bytes == FAT_MAGIC_64 ||
	magic_bytes == FAT_CIGAM || magic_bytes == FAT_CIGAM_64))
	{
		print_archive_member(file, ar_header);
		if (process_macho(file) < 0)
			return (-1);
	}
	file->start = (void *)file->start + ft_atoi(ar_header->ar_size) - offset;
	offset = get_str_offset_archive(file, (struct ar_hdr *)((void *)file->start
				+ sizeof(struct ar_hdr)));
	return (0);
}

int		parse_archive_member(t_infile *file, struct ar_hdr *ar_header)
{
	if (protect(file, (void *)ar_header + sizeof(struct ar_hdr)
	+ ft_atoi(ar_header->ar_size)) < 0)
		return (-1);
	file->start = (void *)file->start + SARMAG;
	archive_fw_symdef(file, (struct ar_hdr *)file->start);
	while ((void *)file->start < (void *)file->save + file->ar_sz)
	{
		if (parse_archive_member_work(file, ar_header) < 0)
			return (-1);
	}
	return (0);
}

int		process_archive(t_infile *file)
{
	struct ar_hdr *ar_header;

	if (protect(file, (void *)file->start + SARMAG) < 0)
		return (error_gen("corrupted header"));
	if (ft_strncmp((void *)file->start, ARMAG, SARMAG))
		return (1);
	if (protect(file, (void *)file->start + SARMAG + sizeof(struct ar_hdr)) < 0)
		return (error_gen("corrupted archive header"));
	ar_header = (void *)file->start + SARMAG;
	print_file_type(file, "Archive : ");
	parse_archive_member(file, ar_header);
	return (0);
}
