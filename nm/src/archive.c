/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:41:54 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/03 18:53:17 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int	print_archive_member(t_infile *file, struct ar_hdr *ar_header)
{
	char *name;
	int ret;

	ret = 0;
	name = NULL;
	if (!ft_strncmp(ar_header->ar_name, AR_EFMT1, ft_strlen(AR_EFMT1)))
	{
		name = (char *)ar_header + sizeof(struct ar_hdr);
		ret = ft_atoi((char *)ar_header->ar_name + ft_strlen(AR_EFMT1));
	}
	else
		name = ar_header->ar_name;
	ft_printf("\n%s(%s):\n", file->filename, name);
	return (ret);
}

int	parse_archive_member(t_infile *file, struct ar_hdr *ar_header)
{
	void	*save;
	int		offset;

	offset = 0;
	save = file->start;
	if ((void *)ar_header + sizeof(struct ar_hdr) + ft_atoi(ar_header->ar_size)
		> (void *)file->start + file->sz)
		return (-1);
	file->start = (void *)ar_header + sizeof(struct ar_hdr) + ft_atoi(ar_header->ar_size);
	while ((void *)file->start < (void *)save + file->sz)
	{
		ar_header = file->start;
		offset = print_archive_member(file, ar_header);
		file->start = (void *)file->start + sizeof(struct ar_hdr) + offset;
		//ft_print_mem(file->start, 32);
		process_fat(file);
		file->start = (void *)file->start + ft_atoi(ar_header->ar_size) - offset;
	}
	return (0);
}

int	process_archive(t_infile *file)
{
	struct ar_hdr *ar_header;

	if ((void *)file->start + SARMAG > (void *)file->start + file->sz)
		return (error_gen("corrupted header"));
	if (ft_strncmp((char *)file->start, ARMAG, SARMAG))
		return (1);
	if ((void *)file->start + SARMAG + sizeof(struct ar_hdr) > (void *)file->start + file->sz)
		return (error_gen("corrupted archive header"));
	ar_header = (void *)file->start + SARMAG;
	parse_archive_member(file, ar_header);
	return (0);
}
