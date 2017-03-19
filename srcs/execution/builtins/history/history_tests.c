#include "libft.h"
#include "shell_env.h"
#include "errors.h"

#include "abstract_list.h"
#include "utils.h"
#include "uint.h"

#include "history.h"
#include "history_substitutions.h"

#define NB_SUB_TESTS 11

void	substitution_test()
{

	int	i = 0;
	char *tests[] = {"!!", "!!!!", "echo !!", "!2", "!-2", "echo !0", \
					"!-0", "!6534", "!-6", "!fi grj", "exho !?ou", NULL};//echo !#"
	char	**str;

	// ft_putendl(get_nth_word("echo coucou \"re test\"", 2));
	str = malloc(sizeof(char *) * NB_SUB_TESTS);
	while (i < NB_SUB_TESTS)
	{
		str[i] = ft_strdup(tests[i]);
		i++;
	}
	i = 0;
	ft_putendl("\n---- HISTORY SUBSTITUTION TESTS --------\n");
	ft_putendl("Current history list: ");
	print_history(get_shell_env()->history, 0);
	while (str[i])
	{
		ft_putstr("\n---- line = \"");
		ft_putstr(str[i]);
		ft_putendl("\" ----\n");
		history_substition(&str[i]);
		ft_putstr("after sub = \"");
		ft_putstr(str[i]);
		ft_putendl("\"");
		i++;
	}
}

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