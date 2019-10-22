/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:21:20 by tmaraval          #+#    #+#             */
/*   Updated: 2019/10/22 16:56:36 by tmaraval         ###   ########.fr       */
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

    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

