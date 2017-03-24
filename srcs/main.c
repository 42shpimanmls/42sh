#include <stdlib.h>
#include "ftsh.h"
#include "init/init.h"
#include <stdio.h>
#include "errors.h"
#include "history_substitutions.h"
#include "parse_input/print_syntax_tree.h"
#include "execution/execute_syntax_tree.h"

static void		main_loop(void)
{
	t_shell_env *shell_env;

	shell_env = get_shell_env();
	set_error(NO_ERROR);
	read_input();
	/*if (get_error() != NO_ERROR)
		return ;*/
	if (history_substitution(&shell_env->input_string))
	{
		ft_strdel(&shell_env->input_string);
		return ;
	}
	add_to_history_list(&shell_env->history, create_history_entry(shell_env->input_string));
	break_input();
	if (get_error() != NO_ERROR)
		return ;
	parse_input();
	if (get_error() != NO_ERROR)
		return ;
	ft_strdel(&get_shell_env()->input_string);
	print_command_list(get_shell_env()->syntax_tree, 0);
	if (get_error() != NO_ERROR)
		return ;
	execute_command_list(get_shell_env()->syntax_tree);
	delete_command_list(&get_shell_env()->syntax_tree);
}

int				main(int ac, char **av)
{
	setbuf(stdout, NULL);
	init(ac, av);
	while (get_shell_env()->should_run)
		main_loop();
	print_name_and_error(get_error());
	if (get_error() == NO_ERROR)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}
