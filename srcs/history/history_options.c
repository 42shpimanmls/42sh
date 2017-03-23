#include <libft.h>
#include "history_options.h"
#include "errors.h"

void			print_history_options(t_hist_opt *options)
{
	int i = 0;

	ft_putstr("selected options are the following: ");
	if (options->c)
		ft_putstr("c, ");
	if (options->d)
		ft_putstr("d, ");
	if (options->a)
		ft_putstr("a, ");
	if (options->n)
		ft_putstr("n, ");
	if (options->w)
		ft_putstr("w, ");
	if (options->r)
		ft_putstr("r, ");
	if (options->p)
		ft_putstr("p, ");
	if (options->s)
		ft_putstr("s, ");
	if (options->offset)
		ft_printf("offset: %s, ", options->offset);
		if (options->args && options->args[0])
		{
			while (options->args[i] && options->args[i][0])
			{
				ft_printf("arg%d: %s, ", i, options->args[i]);
				i++;
			}
		}
	ft_putchar('\n');

}

void			free_history_options(t_hist_opt *options)
{
	if (options->offset)
	{
		ft_putendl(options->offset);
		ft_strdel(&(options->offset));
	}
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
				options->offset = ft_strdup(++arg); // ++arg
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