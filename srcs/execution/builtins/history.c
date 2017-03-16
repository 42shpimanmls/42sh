#include "shell_env.h"
#include "history.h"
#include "builtin_def.h"
#include "abstract_list.h"

/*******   move this to utils (from lem_me.c) ******/


static bool	str_is_digits(char const *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str += 1;
	}
	return (true);
}


/********/

void		history_test()
{
	char 	*print[] = {"history"};
	char	*print_offset[] = {"history", "3"};
	// char	*delete_entry[] = {"history", "-d3"};
	// char	*delete_entry2[] = {"history", "-d", "3"};
	char	*error1[] = {"history", "l"}; // numeric argument required
	char	*error2[] = {"history", "3", "coucou"}; // too many args
	// char	*error3[] = {"history", "-ar"}; // more than one option from anrw

	ft_putendl("----- HISTORY TESTS ------");

	ft_putendl("PRINT: ");
	builtin_history(1, print);
	ft_putendl("PRINT_last_3: ");
	builtin_history(2, print_offset);
	ft_putendl("ERROR_NUM_ARG: ");
	builtin_history(2, error1);
	ft_putendl("ERROR_2MANY_ARGS: ");
	builtin_history(3, error2);

	// builtin_history(2, delete_entry);
	// builtin_history(2, print_offset);
	// builtin_history(3, delete_entry2);
	// builtin_history(2, print_offset);

	ft_putendl("--------------------------\n\n");
}

void		print_history(t_history *history, int start)
{
	int		i;

	i = 1;
	while (history)
	{
		if (i > start)
		{
			ft_putnbr(i);
			ft_putstr("  ");
			ft_putendl(history->line);
		}
		i++;
		history = history->next;
	}
}

void		print_history_n(bool more_args, char *n, t_history *history)
{
	if (more_args)
		ft_putendl_fd("history: too many arguments", 2); //return error_func
	else
		print_history(history, list_count((t_abstract_list *)history) - ft_atoi(n));
}
/*


history [-c] [-d offset] [n] or history -awrn [filename] or history -ps arg [arg...]

	errors
	sh: history: cannot use more than one of -anrw
*/
/*
void		hist_parse_options(int argc, char **argv)
{

}*/

BUILTIN_RET	builtin_history(BUILTIN_ARGS)
{
	int			i;
	// t_hist_opt	options;
	t_history	*history;

	history = get_shell_env()->history;
	i = 1;
	if (argc == 1)
		print_history(history, 0);
	else
	{
		while (i < argc)
		{
			if (*argv[i] == '-')
			{
				;// hist_parse_options();
			}
			else if (str_is_digits(argv[i]))
			{
				print_history_n(i + 1 < argc, argv[i], history);
				break; // return print_hist_n
			}
			else
				ft_putendl_fd("history: numeric argument required", 2); // ret err_func
			i++;
		}
	}
}
