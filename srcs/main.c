#include "break_input/tokenizer/token_def.h"
#include <stdlib.h>
#include "shell_env.h"
#include "init/init.h"
#include <edit_input.h>
#include <stdio.h>
#include "utils.h"

int main(int ac, char **av, char **env)
{
	/*printf("\nget_token_def(OR_TOKID):\n");
	print_token_def(get_token_def(OR_TOKID));
	putchar('\n');

	printf("\nget_matching_operator(\"&\"):\n");
	print_token_def(get_matching_operator("&"));
	putchar('\n');*/

	char 		*line;

	(void)ac;
	(void)av;

	init(env);

	print_token_defs();

	event_callback_test();

	line = edit_input();
	ft_printf("return edit_input = %s\n", line);

	//CALL BREAK_INPUT(char *line);

	return (EXIT_SUCCESS);
}
