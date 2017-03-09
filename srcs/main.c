#include "break_input/tokenizer/token_def.h"
#include <stdlib.h>

#include <stdio.h>

int main(void)
{
	print_token_defs();

	printf("\nget_token_def(OR_TOKID):\n");
	print_token_def(get_token_def(OR_TOKID));
	putchar('\n');

	printf("\nget_matching_operator(\"&\"):\n");
	print_token_def(get_matching_operator("&"));
	putchar('\n');

	return (EXIT_SUCCESS);
}
