#include <BCUnit/BCUnit.h>
#include <BCUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>

static int maxi(int i1, int i2)
{
	return (i1 > i2) ? i1 : i2;
}

static void test_maxi(void)
{
	CU_ASSERT(maxi(0,2) == 2);
	CU_ASSERT(maxi(0,-2) == 0);
	CU_ASSERT(maxi(2,2) == 0);
}

static void print_error(void)
{
	if (CU_get_error() != CUE_SUCCESS)
		printf("Error: %s\n",CU_get_error_msg());
}

int main(void)
{
	CU_ErrorCode	result;

	// Declare
	CU_TestInfo		tests[] = {
	  { "test_pTest_autobuild", test_maxi },
	  CU_TEST_INFO_NULL,
	};
	CU_SuiteInfo	suites[] = {
		{ "test_pSuite_autobuild", NULL, NULL, NULL, NULL, tests },
		CU_SUITE_INFO_NULL
	};

	// Init
	CU_initialize_registry();
	print_error();

	// Register
	CU_register_suites(suites);
	print_error();

	// Run
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
