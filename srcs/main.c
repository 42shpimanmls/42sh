#include <stdlib.h>
#include "ftsh.h"
#include "init/init.h"
#include <stdio.h>
#include "errors.h"
#include "history_substitutions.h"

static void		main_loop(void)
{
	set_error(NO_ERROR);
	read_input();
	/*if (get_error() != NO_ERROR)
		return ;*/
	history_substitution(&get_shell_env()->input_string);
	break_input();
	if (get_error() != NO_ERROR)
		return ;
	ft_strdel(&get_shell_env()->input_string);
	parse_input();
	/*if (get_error() != NO_ERROR)
		return ;*/
	//execute_tree();
}

int				main(int ac, char **av)
{
	setbuf(stdout, NULL);
	init(ac, av);
	while (get_shell_env()->should_run)
		main_loop();
	print_error_msg(get_error());
	if (get_error() == NO_ERROR)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}
