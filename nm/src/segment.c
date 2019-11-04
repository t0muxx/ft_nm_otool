/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 11:21:28 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/04 16:40:45 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		parse_segment_64(t_infile *file, struct load_command *lc)
{
	struct segment_command_64	*sg;
	uint32_t					nsects;
	void						*sections;
	int							id;

	id = 0;
	sg = (struct segment_command_64 *)lc;
	nsects = reverse_32(file->type == IS_BE_64, sg->nsects);
	sections = (void *)sg + sizeof(struct segment_command_64);
	while (nsects--)
	{
		lst_section_append(&file->sections, lst_section_new(sections, id));
		if (protect(file, (void *)sections + sizeof(struct section_64)) < 0)
			return (0);
		sections = (void *)sections + sizeof(struct section_64);
		id++;
	}
	return (0);
}

int		parse_segment_32(t_infile *file, struct load_command *lc)
{
	struct segment_command	*sg;
	uint32_t				nsects;
	void					*sections;
	int						id;

	id = 0;
	sg = (struct segment_command *)lc;
	nsects = reverse_32(file->type == IS_BE, sg->nsects);
	sections = (void *)sg + sizeof(struct segment_command);
	while (nsects--)
	{
		lst_section_append(&file->sections, lst_section_new(sections, id));
		if (protect(file, (void *)sections + sizeof(struct section)) < 0)
			return (0);
		sections = (void *)sections + sizeof(struct section);
		id++;
	}
	return (0);
}

int		parse_segment(t_infile *file, struct load_command *lc)
{
	if (file->type == IS_32 || file->type == IS_BE)
	{
		if (protect(file, (void *)lc + sizeof(struct segment_command)) < 0)
			return (0);
		return (parse_segment_32(file, lc));
	}
	if (file->type == IS_64 || file->type == IS_BE_64)
	{
		if (protect(file, (void *)lc + sizeof(struct segment_command_64)) < 0)
			return (0);
		return (parse_segment_64(file, lc));
	}
	return (0);
}
