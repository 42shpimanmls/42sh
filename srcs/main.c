#include "break_input/tokenizer/token_def.h"
#include <stdlib.h>
#include "shell_env.h"
#include <init.h>
#include <edit_input.h>
#include <stdio.h>

int main(int ac, char **av, char **env)
{
	/*print_token_defs();

	printf("\nget_token_def(OR_TOKID):\n");
	print_token_def(get_token_def(OR_TOKID));
	putchar('\n');

	printf("\nget_matching_operator(\"&\"):\n");
	print_token_def(get_matching_operator("&"));
	putchar('\n');*/

	char 		*line;

	(void)ac;
	(void)av;
	init(env);
	//ft_puttab(global->env);

	line = edit_input();
	ft_printf("return edit_input = %s\n", line);

	//CALL BREAK_INPUT(char *line);

	return (EXIT_SUCCESS);
}
