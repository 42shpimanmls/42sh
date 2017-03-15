#include "break_input/tokenizer/token_def.h"
#include <stdlib.h>
#include "shell_env.h"
#include "init/init.h"
#include <edit_input.h>
#include <stdio.h>
#include "utils.h"
#include "abstract_list.h"
#include "break_input/tokenizer/token.h"

void test_tokens(void)
{
	t_token *token;
	t_token *list;

	print_token_defs();
	list = NULL;
	ft_putendl("TOKENS TEST:");
	token = construct_token("1337", '<');
	list_push_back((t_abstract_list**)&list, (t_abstract_list*)token);
	token = construct_token("1337", ' ');
	list_push_back((t_abstract_list**)&list, (t_abstract_list*)token);
	token = construct_token(";", 'e');
	list_push_back((t_abstract_list**)&list, (t_abstract_list*)token);
	token = construct_token("echo", ' ');
	list_push_back((t_abstract_list**)&list, (t_abstract_list*)token);
	print_tokens(list);
	ft_putendl("DONE TOKENS TEST");
}

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

	test_tokens();
	event_callback_test();

	line = edit_input();
	ft_printf("return edit_input = %s\n", line);

	//CALL BREAK_INPUT(char *line);

	return (EXIT_SUCCESS);
}
