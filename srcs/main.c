#include <stdlib.h>
#include "shell_env.h"
#include "ftsh.h"
#include "init/init.h"
#include <stdio.h>
#include "utils.h"
#include "abstract_list.h"
#include "break_input/token.h"

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
