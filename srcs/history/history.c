#include "history.h"
#include "history_substitutions.h"
#include "errors.h"
#include "abstract_list.h"
#include "utils.h"

#include "history_debug.h"

static void		hist_parse_options(int argc, char **argv, t_hist_opt *options)
{
	int			i;

	i = 1;
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

int				builtin_history(int argc, char **argv)
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
