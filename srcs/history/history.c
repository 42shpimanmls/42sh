#include "history.h"
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
		if (argv[i][0] == '-')
			get_hist_options(argv[i], options);
		else
		{
			options->args = copy_array(argv, i, argc);
			return;
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
			load_history(get_shell_env(), filename, 0); // saved position in file
	}
}

static void		execute_options(t_history **history, t_hist_opt options)
{
	 /*
		 -p  Perform history substitution on the args and display the result
        on the standard output, without storing the results in the history list.

    	-s   The args are added to the end of the history list as a single entry.


    	DON'T SAVE IN HISTORY LIST
    */
char	*args;
	if (options.s || options.p)
	{
		if (options.s)
		{
			if ((args = array_to_str(options.args)))
				add_to_history_list(&get_shell_env()->history, \
					create_history_entry(args));
		}
	}
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

	set_error(NO_ERROR); // set before?
	ft_bzero(&options, sizeof(options));
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
	{
		#ifdef HISTORY_DEBUG
			ft_putendl("EXECUTING HISTORY BUILTIN");
			print_history_options(&options);
		#endif

		execute_options(&get_shell_env()->history, options);
	}
	free_history_options(&options);

	// return must_save or not (actually delete  - if has already been added?)
}
