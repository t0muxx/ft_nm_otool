/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:21:20 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/24 13:42:04 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_nm.h"
#include "tests.h"
#include <cmocka.h>

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_process_infile_ok),
		cmocka_unit_test(test_process_infile_size_0),
		cmocka_unit_test(test_process_infile_perm_0),
		cmocka_unit_test(test_process_infile_no_exsist),
		cmocka_unit_test(test_process_header_ok_32),
		cmocka_unit_test(test_process_header_ok_64),
		cmocka_unit_test(test_process_header_ok_32_big_endian),
		cmocka_unit_test(test_process_header_ok_64_big_endian),
		cmocka_unit_test(test_process_header_ko),
		cmocka_unit_test(test_section_parsing_ok),
		cmocka_unit_test(test_section_parsing_32_ok),

    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

