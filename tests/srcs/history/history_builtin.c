#include <libft.h>

#include "shell_env.h"
#include "history.h"
#include "ftsh.h"

#define HIST_TESTFILE "history_test_file"

void	initialize_history()
{
	char *av[] = {"42sh"};
	init(1, av);
	load_history(get_shell_env(), HIST_TESTFILE);

	#ifdef BANG_TEST_VERBOSE
	ft_putendl("\nCurrent history list: ");
	print_history(get_shell_env()->history, 0);
	#endif
}