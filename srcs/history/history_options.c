#include <libft.h>
#include "history_options.h"
#include "errors.h"

void			free_history_options(t_hist_opt *options)
{
	if (options->offset)
		ft_strdel(&(options->offset));
	if (options->args && options->args[0])
		ft_freetabchar(options->args);
}

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
	if (c == 'a')
		options->a = 1;
	else if (c == 'w')
		options->w = 1;
	else if (c == 'r')
		options->r = 1;
	else if (c == 'n')
		options->n = 1;
	if (no_other_anrw(options))
		return (0);
	return (-1);
}

static bool	check_cd_opt(char **arg, t_hist_opt *options)
{
	if (**arg == 'c')
	{
		options->c = 1;
		return (1);
	}
	else if (**arg == 'd')
	{
		options->d = 1;
		if (*(*arg + 1))
			options->offset = ft_strdup(++(*arg));
		return (1);
	}
	return (0);
}

void		get_hist_options(char *arg, t_hist_opt *options)
{
	options->ac++;
	arg++;
	while (arg && *arg)
	{
		if (check_cd_opt(&arg, options))
			;
		else if (ft_strchr("anrw", *arg))
		{
			if (get_anrw_options(*arg, options) < 0)
			{
				error_builtin("history", NULL, ANRW);
				return ;
			}
		}
		else if (*arg == 'p')
			options->p = 1;
		else if (*arg == 's')
			options->s = 1;
		else
		{
			error_builtin("history", ft_strdup(arg), INVALID_OPTION);
			return ;
		}
		arg++;
	}
}