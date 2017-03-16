#include "shell_env.h"
#include "history.h"
#include "builtin_def.h"
#include "abstract_list.h"

/*******   move this to utils (from lex_me.c) ******/

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

void list_double_push_back(t_history **list, t_history *new) // make a double abstract list
{
	t_history *tmp;

	if (*list == NULL)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

/********/

void		history_test()
{
	char 	*print[] = {"history"};
	char	*print_offset[] = {"history", "3"};
	char	*clear_hist[] = {"history", "-c"};
	char	*delete_entry[] = {"history", "-d3"};
	// char	*delete_entry2[] = {"history", "-d", "3"};
	// char	*hist_to_file[] = {"history", "-w", "file", NULL};
	// char	*hist_to_histfile[] = {"history", "-w"};
	char	*error1[] = {"history", "l"}; // numeric argument required
	char	*error2[] = {"history", "3", "coucou"}; // too many args
	// char	*error3[] = {"history", "-ar"}; // more than one option from anrw

	ft_putendl("----- HISTORY TESTS ------");

	ft_putendl("PRINT: ");
	builtin_history(1, print);
	ft_putendl("PRINT_last_3: ");
	builtin_history(2, print_offset);
	// ft_putendl("HIST_TO_FILE");
	// builtin_history(3, hist_to_file);
	// builtin_history(2, hist_to_histfile);
	ft_putendl("PRINT AFTER DEL_ENTRY 3");
	builtin_history(2, delete_entry);
	builtin_history(1, print);
	// builtin_history(3, delete_entry2);
	// builtin_history(2, print_offset);
	ft_putendl("CLEAR_HISTORY");
	builtin_history(2, clear_hist);
	ft_putendl("PRINT: ");
	builtin_history(1, print);
	ft_putendl("ERROR_NUM_ARG: ");
	builtin_history(2, error1);
	ft_putendl("ERROR_2MANY_ARGS: ");
	builtin_history(3, error2);



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
			ft_putstr("  "); // alignment // most digits
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

void		get_hist_option(char *c, t_hist_opt *options)
{
	if (*c == 'c') // clean before append but after substitutions
		options->c = 1;
	else if (*c == 'd')
	{
		options->d = 1;
		if (str_is_digits(++c))
			options->offset = ft_atoi(c);
	}
	else if (*c == 'a')
		options->a = 1;
	else if (*c == 'w') // ignored if -d
		options->w = 1;
	else if (*c == 'r')
		options->r = 1;
	else if (*c == 'n') // ?
		options->n = 1;
	// substitutions before clean
	else if (*c == 'p') // make substitutions but don't execute or save in history
		options->p = 1;
	else if (*c == 's')
		options->s = 1;
}

void		init_hist_opt(t_hist_opt *options)
{
	options->c = 0;
	options->d = 0;
	options->a = 0;
	options->w = 0;
	options->r = 0;
	options->n = 0;
	options->p = 0;
	options->s = 0;
	options->args = NULL;
}

void		hist_parse_options(int argc, char **argv, t_hist_opt *options)
{
	int			i;

	i  = 1;
	while (i < argc)
	{
		if (*argv[i] != '-')
		{
			options->args = &argv[i];
			return;
		}
		while (*argv[i])
		{
			get_hist_option(&*argv[i], options);
			argv[i]++;
		}
		i++;
	}
}

void		execute_options(t_history **history, t_hist_opt options)
{
	if (options.s || options.p)
	{;}
	else if (options.d || options.c)
	{
		if (options.c)
			clear_history_list(history);
		else
		{
			delete_history_entry(history, options.offset);
		}
	}
	else if (options.w || options.a) // what's the difference?
	{
		if (options.args && options.args[0])
			hist_to_file(*history, options.args[0]);
		else
			hist_to_file(*history, HISTFILE);
	}
}

BUILTIN_RET	builtin_history(BUILTIN_ARGS)
{
	int			i;
	t_history	*history;
	t_hist_opt	options;

	init_hist_opt(&options);
	history = get_shell_env()->history;
	i = 1;
	if (argc == 1)
		print_history(history, 0);
	else
	{
		if (*argv[1] == '-')
			hist_parse_options(argc, argv, &options);
		else if (str_is_digits(argv[i]))
			print_history_n(i + 1 < argc, argv[i], history);
		else
			ft_putendl_fd("history: numeric argument required", 2); // ret err_func
	}
	//check_options(options); // check if more than one of awnr
	execute_options(&get_shell_env()->history, options);
}
