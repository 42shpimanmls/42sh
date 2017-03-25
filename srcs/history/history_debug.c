#include "history_debug.h"

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

void	print_range(t_range *range)
{
	ft_putendl("<range>");
	ft_putendl("start: ");
	ft_putnbr(range->start);
	ft_putchar('\n');
	ft_putendl("end: ");
	ft_putnbr(range->end);
	ft_putchar('\n');
	ft_putendl("</range>");
}