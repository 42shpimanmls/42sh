#include "history.h"
#include "abstract_list.h"
#include "utils.h"

void add_to_history_list(t_history **list, t_history *new)
{
	t_history *tmp;

	if (*list == NULL)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

t_history	*create_history_entry(char *line)
{
	t_history *new;

	new = (t_history *)memalloc_or_die(sizeof(t_history));
	new->line = ft_strdup(line);
	new->appended = false;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	load_history(t_shell_env *shell_env, char *filename, int position)
{
	char	*line;
	char	*tmp;
	int		fd;

	(void)position; // should determine where to start in file (-n option)
	if (filename)
		fd = open(filename, O_RDWR | O_CREAT, 0666); // protect in case no rights, etc + set_error
	else
		fd = open(HISTFILE, O_RDWR | O_CREAT, 0666);
	if (fd > 0)
	{
		while ((line = ft_getline(fd)))
		{
			tmp = ft_strjoin(line, "\n");
			add_to_history_list(&shell_env->history, create_history_entry(tmp));
			ft_strdel(&line);
			ft_strdel(&tmp);
		}
		close(fd);
	}
}
