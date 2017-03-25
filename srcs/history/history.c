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
		if (argv[i][0] == '-')
			get_hist_options(argv[i], options);
		else
		{
			options->args = copy_array(argv, i, argc);
			break;
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

static bool		args_manipulation(t_history **history, t_hist_opt options)
{
	char	*args;
	int		i;

 /*
		 -p  Perform history substitution on the args and display the result
        on the standard output, without storing the results in the history list.

    	-s   The args are added to the end of the history list as a single entry.


    	DON'T SAVE IN HISTORY LIST!!!! => bool returned
    */
    i = 0;
    if (options.s)
    {
		// todo: add a \n at end of str
    	if ((args = array_to_str(options.args)))
    	{
    		add_to_history_list(history, \
    			create_history_entry(args));
			ft_strdel(&args);
    	}
    	else
		// if no args the line IS SAVED AS IS e.g. 'history -s', 'history -s -a'
    		return (true);
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
		/*
			sh-3.2$ history -p "!!"
			history -p "last_command"
			last_command
		*/
		//ft_putstr(\command_name_and_options\);
		if ((args = array_to_str(options.args)))
		{
			ft_putendl(args);
			ft_strdel(&args);
		}
		// print line with substitutions without quotes
	}
	return (false);
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

static bool		execute_options(t_history **history, t_hist_opt options)
{
	if (options.s || options.p)
		return (args_manipulation(history, options));
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
	return (true);
}

BUILTIN_RET	builtin_history(BUILTIN_ARGS)
{
	int			i;
	t_history	*history;
	t_hist_opt	options;
	bool		should_save;

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

		if (!(should_save = execute_options(&get_shell_env()->history, options)))
			; // delete from list if already added, or return dont_save
	}
	free_history_options(&options);
	return (STATUS_SUCCESS);
}
