#include "shell_env.h"
#include "history.h"

void		print_history(t_history *history)//, int n) // easier with total nb of entries or list_count func to print n last lines
{
	int	i;

	i = 1;
	while (history)
	{
		ft_putnbr(i++);
		ft_putstr("  ");
		ft_putendl(history->line);
		history = history->next;
	}
}

t_history	*create_history_elem(char *line)
{
	t_history *new;

	new = (t_history *)malloc(sizeof(t_history));
	new->line = ft_strdup(line);
	new->next = NULL;
	new->prev = NULL;
	return(new);
}

void	add_to_history(t_history **history, t_history *new) // keep track of nb of entries?
{
		if (!*history)
			*history = new;
		else if ((*history)->next)
			add_to_history(&(*history)->next, new);
		else
		{
			(*history)->next = new;
			new->prev = *history;
		}
}

void	load_history(t_shell_env *shell_env, char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDWR	| O_CREAT, 0666);
	while (ft_get_next_line(fd, &line) > 0)
	{
		add_to_history(&shell_env->history, create_history_elem(line));
		ft_strdel(&line);
	}
	close(fd);
}
