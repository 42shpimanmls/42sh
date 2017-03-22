#include <libft.h>
#include "execution/builtins/history_options.h"
#include "errors.h"

static bool 	no_other_anrw(t_hist_opt *options)
{
	if (options->a)
	{
		if (options->n || options->r || options->w)
			return (false);
	}
	else if (options->n)
	{
		if (options->a || options->r || options->w)
			return (false);
	}
	else if (options->r)
	{
		if (options->a || options->n || options->w)
			return (false);
	}
	else if (options->w)
	{
		if (options->a || options->r || options->n)
			return (false);
	}
	return (true);
}

static int 	get_anrw_options(char c, t_hist_opt *options)
{
	if (c == 'a') // append
		options->a = 1;
	else if (c == 'w') // ignored if -d // write(on t_hist_opt)
		options->w = 1;
	else if (c == 'r')
		options->r = 1;
	else if (c == 'n') // unnecessary?
		options->n = 1;
	if (no_other_anrw(options))
		return (-1);
	return (0);
}

int		get_hist_options(char *arg, t_hist_opt *options)
{
	arg++;
	while (arg && *arg)
	{
		if (*arg == 'c') // clean before append but after substitutions
			options->c = 1;
		else if (*arg == 'd')
		{
			options->d = 1;
			if (*(arg + 1))
				options->offset = ft_strdup(arg + 1);
		}
		else if (ft_strchr("anrw", *arg))
		{
			if (get_anrw_options(*arg, options) < 0)
				return (-1);
		}
		// substitutions before clean
		else if (*arg == 'p') // make substitutions but don't execute or save in history
			options->p = 1;
		else if (*arg == 's')
			options->s = 1;
		else
		{
			error_builtin("history", ft_strdup(arg), INVALID_OPTION);
			return (-1);
		}
		arg++;
	}
	return (0);
}