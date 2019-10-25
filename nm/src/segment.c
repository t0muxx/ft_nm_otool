/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 11:21:28 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/25 11:35:12 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	parse_segment_64(t_infile *file, struct load_command *lc)
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
		if ((void *)sections + sizeof(struct section_64) 
				> (void *)file->start + file->sz)
			return ;
		sections = (void *)sections + sizeof(struct section_64);
		id++;
	}
	return ;
}

void	parse_segment_32(t_infile *file, struct load_command *lc)
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
		if ((void *)sections + sizeof(struct section) 
				> (void *)file->start + file->sz)
			return ;
		sections = (void *)sections + sizeof(struct section);
		id++;
	}
	return ;
}

void	parse_segment(t_infile *file, struct load_command *lc)
{
	if (file->type == IS_32 || file->type == IS_BE)
	{
		if ((void *)lc + sizeof(struct segment_command)
				> (void *)file->start + file->sz)
			return ;
		parse_segment_32(file, lc);
	}
	if (file->type == IS_64 || file->type == IS_BE_64)
	{
		if ((void *)lc + sizeof(struct segment_command_64)
				> (void *)file->start + file->sz)
			return ;
		parse_segment_64(file, lc);
	}
	return ;
}
