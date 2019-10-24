/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 11:55:01 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/24 14:18:17 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int		cnt_section(t_section *sections)
{
	int i;

	i = 0;
	while (sections)
	{
		i++;
		sections = sections->next;
	}
	return (i);
}

void	test_section_parsing_32_ok(void **state)
{
	t_infile *file;
	struct section *sect;

	file = NULL;
	file = process_infile("./files/32_exe_hard");
	process_header(file);
	iter_load_command(file);
	assert_int_equal(cnt_section(file->sections), 25);
	sect = (struct section *)file->sections->section;
	assert_string_equal(sect->sectname, "__text");
	assert_string_equal(sect->segname, "__TEXT");
	assert_int_equal(file->sections->id, 0);
	sect = (struct section *)file->sections->next->next->next->next->next->next->next->next->section;
	assert_string_equal(sect->sectname, "__nl_symbol_ptr");
	assert_string_equal(sect->segname, "__DATA");
	assert_int_equal(file->sections->next->next->next->next->next->next->next->next->id, 0);
	lst_section_free(file->sections);
	free(file);
}

void	test_section_parsing_ok(void **state)
{
	t_infile *file;
	struct section_64 *sect;

	file = NULL;
	file = process_infile("./files/64_exe_easy");
	process_header(file);
	iter_load_command(file);
	assert_int_equal(cnt_section(file->sections), 3);
	sect = (struct section_64 *)file->sections->section;
	assert_string_equal(sect->sectname, "__text");
	assert_string_equal(sect->segname, "__TEXT");
	assert_int_equal(file->sections->id, 0);
	lst_section_free(file->sections);
	free(file);

}
