#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "tests.h"
#include <CUnit/Console.h>
#include <libft.h>

static void print_error(void)
{
	if (CU_get_error() != CUE_SUCCESS)
		printf("Error: %s\n",CU_get_error_msg());
}

int main(int argc, char **argv)
{
	CU_ErrorCode	result;

	// Declare
	CU_TestInfo		binary_tests[] = {
	  { "42sh -c \"\"", empty_command_string },
	  { "42sh -c \"'\"", unclosed_quote },
	  { "42sh -c \"\\\"\"", unclosed_double_quote },
	  CU_TEST_INFO_NULL,
	};
	CU_SuiteInfo	suites[] = {
		{ "Binary tests", NULL, NULL, NULL, NULL, binary_tests },
		CU_SUITE_INFO_NULL
	};

	// Init
	CU_initialize_registry();
	print_error();

	// Register
	CU_register_suites(suites);
	print_error();

	// Run
	if (argc > 1 && ft_strequ(argv[1], "-i"))
		CU_console_run_tests();
	else
		CU_basic_run_tests();

	print_error();

	// Get result
	if (CU_get_number_of_failures() > 0)
		result = EXIT_FAILURE;
	else
		result = EXIT_SUCCESS;
	print_error();

	// Clean
	CU_cleanup_registry();
	print_error();

	return (result);
}
