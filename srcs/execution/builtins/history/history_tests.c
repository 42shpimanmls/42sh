#include "libft.h"
#include "shell_env.h"
#include "errors.h"

#include "abstract_list.h"
#include "utils.h"
#include "uint.h"

#include "history.h"
#include "history_substitutions.h"

void		history_test()
{
	char 	*print[] = {"history"};
	char	*print_offset[] = {"history", "3"};
	char	*clear_hist[] = {"history", "-c"};
	// char	*delete_entry[] = {"history", "-d3"};
	char	*delete_entry2[] = {"history", "-d", "3", NULL};
	// char	*hist_to_file[] = {"history", "-w", "file", NULL};
	// char	*hist_append_file[] = {"history", "-a", "file", NULL};
	// char	*hist_to_histfile[] = {"history", "-w"};
	char	*error1[] = {"history", "l"};
	char	*error2[] = {"history", "3", "coucou"};
	char	*error3[] = {"history", "-d", "slijg", NULL};
	char	*error4[] = {"history", "-d", "8797", NULL};

	// char	*error3[] = {"history", "-ar"}; // more than one option from anrw

	ft_putendl("----- HISTORY TESTS ------");

	ft_putendl("PRINT: ");
	builtin_history(1, print);
	ft_putendl("PRINT_last_3: ");
	builtin_history(2, print_offset);
	ft_putendl("HIST_TO_FILE");
	// builtin_history(3, hist_to_file);
	// builtin_history(3, hist_append_file);
	// builtin_history(2, hist_to_histfile);
	ft_putendl("PRINT AFTER DEL_ENTRY 3");
	// builtin_history(2, delete_entry);
	// builtin_history(1, print);
	builtin_history(3, delete_entry2);
	builtin_history(2, print_offset);
	ft_putendl("CLEAR_HISTORY");
	builtin_history(2, clear_hist);
	ft_putendl("PRINT: ");
	builtin_history(1, print);
	ft_putendl("ERROR_NUM_ARG: ");
	builtin_history(2, error1);
	ft_putendl("ERROR_2MANY_ARGS: ");
	builtin_history(3, error2);
	ft_putendl("ERROR_OUT_OF_RANGE: ");
	builtin_history(3, error3);
	builtin_history(3, error4);




	ft_putendl("--------------------------\n\n");
}