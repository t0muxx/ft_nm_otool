#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
#include "ft_nm.h"


void	test_process_infile_no_exsist(void **state);
void	test_process_infile_perm_0(void **state);
void	test_process_infile_size_0(void **state);
void	test_process_infile_ok(void **state);

void	test_process_header_ok_32(void **state);
void	test_process_header_ok_64(void **state);
void	test_process_header_ok_32_big_endian(void **state);
void	test_process_header_ok_64_big_endian(void **state);
void	test_process_header_ko(void **state);
