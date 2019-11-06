/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 11:21:28 by tmaraval          #+#    #+#             */
/*   Updated: 2019/11/06 11:29:23 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		parse_segment_64(t_infile *file, struct load_command *lc)
{
	struct segment_command_64	*sg;
	uint32_t					nsects;
	void						*sections;

	sg = (struct segment_command_64 *)lc;
	nsects = reverse_32(file->type == IS_BE_64, sg->nsects);
	sections = (void *)sg + sizeof(struct segment_command_64);
	while (nsects--)
	{
		if (!ft_strcmp(((struct section_64 *)sections)->segname, "__TEXT")
		&& !ft_strcmp(((struct section_64 *)sections)->sectname, "__text"))
		{
			file->text_sz = reverse_64(file->type == IS_BE_64,
					((struct section_64 *)sections)->size);
			file->text_offs = reverse_32(file->type == IS_BE_64,
					((struct section_64 *)sections)->offset);
			file->text_addr = reverse_64(file->type == IS_BE_64,
					((struct section_64 *)sections)->addr);
			return (1);
		}
		if (protect(file, (void *)sections + sizeof(struct section_64)) < 0)
			return (0);
		sections = (void *)sections + sizeof(struct section_64);
	}
	return (0);
}

int		parse_segment_32(t_infile *file, struct load_command *lc)
{
	struct segment_command	*sg;
	uint32_t				nsects;
	void					*sections;

	sg = (struct segment_command *)lc;
	nsects = reverse_32(file->type == IS_BE, sg->nsects);
	sections = (void *)sg + sizeof(struct segment_command);
	while (nsects--)
	{
		if (!ft_strcmp(((struct section *)sections)->segname, "__TEXT")
		&& !ft_strcmp(((struct section *)sections)->sectname, "__text"))
		{
			file->text_sz = reverse_32(file->type == IS_BE,
					((struct section *)sections)->size);
			file->text_offs = reverse_32(file->type == IS_BE,
					((struct section *)sections)->offset);
			file->text_addr = reverse_32(file->type == IS_BE,
					((struct section *)sections)->addr);
			return (1);
		}
		if (protect(file, (void *)sections + sizeof(struct section)) < 0)
			return (0);
		sections = (void *)sections + sizeof(struct section);
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
