#include "history.h"
#include "history_options.h"
#include "errors.h"
#include "abstract_list.h"
#include "utils.h"

char			**copy_array(char **array, t_uint start, int end)
{
	char	**copy;
	size_t	i;
	size_t size;

	i = 0;
	size = end - start;
	copy = (char **)memalloc_or_die(sizeof(char *) * (size + 1));
	copy[size] = NULL;
	while (i < size)
	{
		copy[i] = ft_strdup(array[start]);
		i++;
		start++;
	}
	return (copy);
}

static int		hist_parse_options(int argc, char **argv, t_hist_opt *options)
{
	int			i;

	i  = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			if (get_hist_options(argv[i], options) < 0)
				return (-1);
		}
		else
		{
			options->args = copy_array(argv, i, argc);
			return (0);
		}
		i++;
	}
	if (options->d && !options->offset)
	{
		if (options->args && options->args[0])
		{
			// if (str_is_digits(options->args[0]))
			// {
				options->offset = ft_strdup(options->args[0]);
			// }
		}
		else
			error_builtin("history", NULL, NEED_NUM);
	}
	return (0);
}

static void		execute_options(t_history **history, t_hist_opt options)
{
	if (options.s || options.p)
	{;}
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
	else if (options.w || options.a)
	{
		if (options.w && options.args && options.args[0])
			hist_to_file(*history, options.args[0], false);
		else if (options.w)
			hist_to_file(*history, HISTFILE, false);
		else if (!options.args)
			hist_to_file(*history, HISTFILE, true);
	}
}

BUILTIN_RET	builtin_history(BUILTIN_ARGS)
{
	int			i;
	t_history	*history;
	t_hist_opt	options;

	set_error(NO_ERROR); // just for unit test purposes, expected to be set before in loop
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
	#ifdef HISTORY_DEBUG
	print_history_options(&options);
	#endif
	if (get_error() == NO_ERROR)
		execute_options(&get_shell_env()->history, options);
	free_history_options(&options);
	// return must_run or must_print_out or must not add to history (already added so in fact delete)
}
