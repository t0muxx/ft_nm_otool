/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:20:27 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/23 15:42:26 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	test_process_header_ko(void **state)
{
	t_infile *infile;

	infile = NULL;
	infile = process_infile("./files/32_corrupt_header");
	assert_non_null(infile);
	assert_int_equal(process_header(infile), -1);
}

void	test_process_header_ok_64_big_endian(void **state)
{
	t_infile *infile;

	infile = NULL;
	infile = process_infile("./files/64_big_endian");
	assert_non_null(infile);
	assert_int_equal(process_header(infile), 0);
	assert_int_equal(infile->type, IS_BE_64);		
}

void	test_process_header_ok_32_big_endian(void **state)
{
	t_infile *infile;

	infile = NULL;
	infile = process_infile("./files/32_big_endian");
	assert_non_null(infile);
	assert_int_equal(process_header(infile), 0);
	assert_int_equal(infile->type, IS_BE);		
}

void	test_process_header_ok_64(void **state)
{
	t_infile *infile;

	infile = NULL;
	infile = process_infile("./files/64_exe_easy");
	assert_non_null(infile);
	assert_int_equal(process_header(infile), 0);
	assert_int_equal(infile->type, IS_64);		
}

void	test_process_header_ok_32(void **state)
{
	t_infile *infile;

	infile = NULL;
	infile = process_infile("./files/32_exe_hard");
	assert_non_null(infile);
	assert_int_equal(process_header(infile), 0);
	assert_int_equal(infile->type, IS_32);		
}
