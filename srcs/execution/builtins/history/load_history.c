#include "shell_env.h"
#include "history.h"
#include "abstract_list.h"
#include "utils.h"

void list_double_push_back(t_history **list, t_history *new);

t_history	*create_history_entry(char *line)
{
	t_history *new;

	new = (t_history *)memalloc_or_die(sizeof(t_history));
	new->line = ft_strdup(line);
	new->appended = false;
	new->next = NULL;
	new->prev = NULL;
	return(new);
}

void	load_history(t_shell_env *shell_env, char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDWR	| O_CREAT, 0666);
	while (ft_get_next_line(fd, &line) > 0)
	{
		list_double_push_back(&shell_env->history, create_history_entry(line));
		ft_strdel(&line);
	}
	close(fd);
}
