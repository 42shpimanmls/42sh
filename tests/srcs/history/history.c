#include <libft.h>
#include "test_utils.h"

#include "shell_env.h"
#include "history/history.h"
#include "ftsh.h"
#include "abstract_list.h"


// #define HISTORY_TEST_VERBOSE

void	initialize_history()
{
	char *av[] = {"42sh"};
	init(1, av);
	load_history(get_shell_env(), HISTFILE);

	#ifdef HISTORY_TEST_VERBOSE
	ft_printf("\nHistory list has been initialized from %s: \n", HISTFILE);
	print_history(get_shell_env()->history, 0);
	#endif
}

/*
	no ret value for builtins for the moment
*/

void	history_add_one()
{
	t_history *history;
	char	str[] = "added\n";
	size_t 	nb;

	history = get_shell_env()->history;
	nb = list_count((t_abstract_list *)history);
	add_to_history_list(&history, create_history_entry(str));
	CU_ASSERT_EQUAL(nb + 1, list_count((t_abstract_list *)history));

	#ifdef HISTORY_TEST_VERBOSE
		ft_putendl("State of history after adding entry \"added\":");
		print_history(history, 0);
	#endif
}

void	history_print()
{
	char	*av[] = {"history"};
	// int ret;

	builtin_history(1, av);
	// CU_ASSERT_EQUAL(ret, 0)

}

void	history_print_offset()
{
	char	*av[][2] = {
						{"history", "0"},
						{"history", "3"}
					};
	// int ret;

	builtin_history(2, av[0]);
	// CU_ASSERT_EQUAL(ret, 0)
	builtin_history(2, av[1]);
	// CU_ASSERT_EQUAL(ret, 0)

}

void	history_delete()
{
	size_t nb;

	char	*av[][3] = {
						{"history", "-d7", NULL},
						{"history", "-d", "1"}
					};

	nb = list_count((t_abstract_list *)get_shell_env()->history) - 1;
	//printf("nb: %zu\n", nb);
	builtin_history(2, av[0]);
	CU_ASSERT_EQUAL(nb, list_count((t_abstract_list *)get_shell_env()->history));
	nb--;

	#ifdef HISTORY_TEST_VERBOSE
		ft_putendl("State of history after deleting entry 7:");
		print_history(get_shell_env()->history, 0);
	#endif

	builtin_history(3, av[1]);
	CU_ASSERT_EQUAL(nb, list_count((t_abstract_list *)get_shell_env()->history));

	#ifdef HISTORY_TEST_VERBOSE
		ft_putendl("State of history after deleting entry 1:");
		print_history(get_shell_env()->history, 0);
	#endif

}

void	history_to_file()
{
	char	*av[][4] = {
						{"history", "-w", "test", NULL}, // should overwrite or create test
						{"history", "-a", "test", NULL}, // shoud do nothing
						{"history", "-a", NULL, NULL} // should append not already appended lines
					};

	builtin_history(3, av[0]);
	CU_ASSERT_NOT_EQUAL(open("test", O_RDONLY), -1);
	#ifdef HISTORY_TEST_VERBOSE
		ft_printf("This history should have been appended to %s once only:\n", HISTFILE);
		print_history(get_shell_env()->history, 0);
	#endif
	// builtin_history(2, av[1]);

	builtin_history(3, av[1]);
	builtin_history(2, av[2]);
}

void	history_clear()
{
	char *av[] = {"history", "-c"};


	builtin_history(2, av);
	CU_ASSERT_PTR_NULL(get_shell_env()->history);
	#ifdef HISTORY_TEST_VERBOSE
		ft_putendl("State of history after clearing all (should be empty!):");
		print_history(get_shell_env()->history, 0);
	#endif
}

void	history_errors()
{
	char	*av[][3] = {
						{"history", "-l", NULL},
						{"history", "l", NULL},
						{"history", "3", "coucou"},
						{"history", "-d", "slijg"},
						{"history", "-d", "8797"}
						};

	builtin_history(2, av[0]);
	// builtin_history(2, av[1]);
	// builtin_history(3, av[2]);
	builtin_history(3, av[3]);
	builtin_history(3, av[4]);
}

