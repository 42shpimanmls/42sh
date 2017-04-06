#include "history.h"
#include "history_substitutions.h"
#include "history_options.h"
#include "errors.h"
#include "abstract_list.h"
#include "utils.h"

#include "history_debug.h"

static void		hist_parse_options(int argc, char **argv, t_hist_opt *options)
{
	int			i;

	i  = 1;
	while (i < argc)
	{
		if (get_error() != NO_ERROR)
			return ;
		if (argv[i][0] == '-')
			get_hist_options(argv[i], options);
		else
		{
			options->args = copy_array(argv, i, argc);
			break ;
		}
		i++;
	}
	if (get_error() == NO_ERROR && options->d && !options->offset)
	{
		if (options->args && options->args[0])
				options->offset = ft_strdup(options->args[0]);
		else
			error_builtin("history", NULL, NEED_NUM);
	}
}

static void		print_subst_result(char **argv, t_hist_opt options)
{
	int 	i;
	char 	*args;

	i = 0;
	while (i < options.ac)
	{
		ft_putstr(argv[i]);
		ft_putchar(' ');
		i++;
	}
	// print line with substitutions without quotes
	if ((args = array_to_str(options.args)))
	{
		ft_putendl(args);
		ft_puttab(options.args);
		ft_strdel(&args);
	}
}

static void		args_manipulation(t_history **history, t_hist_opt options, char **argv)
{
	char	*args;
	int		i;

    i = 0;
    if (options.s)
    {
		delete_entry_at(history, list_count((t_abstract_list *)*history));
    	if ((args = array_to_str(options.args)))
    	{
    		history_add_with_nl(get_shell_env(), args);
			ft_strdel(&args);
    	}
    }
    else if (options.args)
    {
    	while (options.args[i])
    	{
			/*
				quotes should already have been removed
				+ normal substitution made
				(test with quotes etc when execution loop)
			*/
			history_substitution(&options.args[i]);
			i++;
		}
		print_subst_result(argv, options);
		delete_entry_at(history, list_count((t_abstract_list *)*history));
	}
}

static void		file_manipulation(t_hist_opt options, t_history *history)
{
	char		*filename;

	if (options.args)
			filename = options.args[0];
	else
		filename = NULL;

	// writing in file
	if (options.w || options.a)
	{
		if (options.w)
			hist_to_file(history, filename, false);
		else if (!filename)
			hist_to_file(history, HISTFILE, true);
	}

	//reading file
	else if (options.r || options.n)
	{
		if (options.r)
			load_history(get_shell_env(), filename, 0);
		else
			load_history(get_shell_env(), filename, 1);
	}
}

static void		execute_options(t_history **history, t_hist_opt options, char **argv)
{
	if (options.s || options.p)
		args_manipulation(history, options, argv);
	else if (options.d || options.c)
	{
		if (options.c)
			clear_history_list(history);
		else
		{
			if (!options.offset)
				options.offset = ft_strdup(options.args[0]);
			delete_history_entry(history, options.offset);
		}
	}
	else
		file_manipulation(options, *history);
}

BUILTIN_RET	builtin_history(BUILTIN_ARGS)
{
	int			i;
	t_history	*history;
	t_hist_opt	options;

	set_error(NO_ERROR);
	ft_bzero(&options, sizeof(options));
	options.ac = 1;
	history = get_shell_env()->history;
	i = 1;
	if (argc == 1)
		print_history(history, 0);
	else
	{
		if (*(argv[1]) == '-')
			hist_parse_options(argc, argv, &options);
		else if (str_is_digits(argv[i]))
			print_history_n(i + 1 < argc, argv[i], history);
		else
			error_builtin(argv[0], NULL, NEED_NUM);
	}
	if (get_error() == NO_ERROR)
		execute_options(&get_shell_env()->history, options, argv);
	free_history_options(&options);
	return (get_error());
}
