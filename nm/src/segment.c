/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 11:21:28 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/31 11:00:47 by tmaraval         ###   ########.fr       */
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
	if (reverse_32(file->type == IS_BE_64, sg->cmdsize) != sizeof(struct segment_command_64) + nsects * sizeof(struct section_64))
		return (-1);
	while (nsects--)
	{
		lst_section_append(&file->sections, lst_section_new(sections, id));
		if ((void *)sections + sizeof(struct section_64) 
				> (void *)file->start + file->sz)
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
	if (reverse_32(file->type == IS_BE, sg->cmdsize) != sizeof(struct segment_command) + nsects * sizeof(struct section))
		return (-1);
	while (nsects--)
	{
#ifdef DEBUG_SECTION
		printf("added section : %s for segment : %s\n", ((struct section *)sections)->sectname, ((struct section *)sections)->segname);
#endif
		lst_section_append(&file->sections, lst_section_new(sections, id));
		if ((void *)sections + sizeof(struct section) 
				> (void *)file->start + file->sz)
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
		if ((void *)lc + sizeof(struct segment_command)
				> (void *)file->save + file->sz)
			return (0);
		return (parse_segment_32(file, lc));
	}
	if (file->type == IS_64 || file->type == IS_BE_64)
	{
		if ((void *)lc + sizeof(struct segment_command_64)
				> (void *)file->save + file->sz)
			return (0);
		return (parse_segment_64(file, lc));
	}
	return (0);
}
