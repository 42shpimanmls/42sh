#include <stdlib.h>
#include "ftsh.h"
#include "init/init.h"
#include <stdio.h>
#include "errors.h"

static void		main_loop()
{
	read_input();
	/*if (get_error() != NO_ERROR)
		return ;*/
	break_input();
	if (get_error() != NO_ERROR)
		return ;
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
	return (EXIT_SUCCESS);
}
