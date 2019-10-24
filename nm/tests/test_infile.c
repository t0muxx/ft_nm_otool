/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:09:07 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/24 10:01:37 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"


void	test_process_infile_no_exsist(void **state)
{
	t_infile *infile;
	
	infile = NULL;
	infile = process_infile("./files/ooo");
	assert_null(infile);
	free(infile);
}

void	test_process_infile_perm_0(void **state)
{
	t_infile *infile;
	
	infile = NULL;
	infile = process_infile("./files/perm_0");
	assert_null(infile);
	free(infile);
}

void	test_process_infile_size_0(void **state)
{
	t_infile *infile;
	
	infile = NULL;
	infile = process_infile("./files/size_0");
	assert_null(infile);
	free(infile);
}

void	test_process_infile_ok(void **state)
{
	t_infile *infile;
	
	infile = NULL;
	infile = process_infile("./files/size_4096");
	assert_non_null(infile);
	assert_int_equal(infile->sz, 4096);
	free(infile);
}
