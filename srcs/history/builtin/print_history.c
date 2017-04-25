#include "history.h"
#include "errors.h"
#include "abstract_list.h"

static void	print_blanks(size_t hist_size, int i)
{
	int		len;
	char	*blanks;

	len = ft_intlen(hist_size) - ft_intlen(i) + 2;
	blanks = memalloc_or_die(sizeof(char) * (len + 1));
	blanks[len] = '\0';
	while (--len >= 0)
		blanks[len] = ' ';
	ft_putstr(blanks);
	ft_strdel(&blanks);
}

void		print_history(t_history *history, int start)
{
	int		i;
	size_t	hist_size;

	i = 1;
	hist_size = list_count((t_abstract_list *)history);
	while (history)
	{
		if (i > start)
		{
			ft_printf("    %d", i);
			print_blanks(hist_size, i);
			ft_putstr(history->line);
		}
		i++;
		history = history->next;
	}
}

void		print_history_n(bool more_args, char *n, t_history *history)
{
	if (more_args)
		error_builtin("history", NULL, TOO_MANY_ARGS);
	else
		print_history(history, list_count((t_abstract_list *)history) \
								- ft_atoi(n));
}
