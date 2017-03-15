#include <stdlib.h>
#include "shell_env.h"
#include "ftsh.h"
#include "init/init.h"
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

static void		main_loop()
{
	read_input();
	break_input();
	//parse_input();
	//execute_tree();
}

int				main(int ac, char **av)
{
	setbuf(stdout, NULL);
	init(ac, av);
	while (get_shell_env()->should_run)
		main_loop();
	return (EXIT_SUCCESS);
}
