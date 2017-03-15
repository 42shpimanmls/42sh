#include "shell_env.h"
#include "history.h"
#include "builtin_def.h"
#include "abstract_list.h"

/*******   move this to utils  ******/


static bool	str_is_digits(char const *str)  // from lem_me.c, move to tools
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str += 1;
	}
	return (true);
}

size_t list_count(t_abstract_list *list)
{
	size_t	n;

	n = 0;
	while (list)
	{
		n++;
		list = list->next;
	}
	return (n);
}


/********/

void		print_history(t_history *history, int start)
{
	int		i;

	i = 1;
	while (history)
	{
		if (i > start)
		{
			ft_putnbr(i);
			ft_putstr("  ");
			ft_putendl(history->line);
		}
		i++;
		history = history->next;
	}
}

/*
	[n] 
	-c
	-d offset
	-anrw [filename]
	-ps arg

	errors 
	sh: history: cannot use more than one of -anrw
	*/

BUILTIN_RET	builtin_history(BUILTIN_ARGS)
{
	int			i;
	// t_hist_opt	options;
	t_history	*history;

	history = get_shell_env()->history;
	i = 1;
	if (argc == 1)
		print_history(history, 0);
	else
	{
		while (argv[i])
		{
			if (str_is_digits(argv[i]))
			{
				if (argv[i + 1])
					ft_putendl("history: too many arguments"); //return error_func
				else
					print_history(history, list_count((t_abstract_list *)history) - ft_atoi(argv[i]));
			}
			else if (*argv[i] == '-')
			{
				//hist_parse_options();
				;
			}
			i++;
		}
	}
}
