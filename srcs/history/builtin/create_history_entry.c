#include "history.h"

t_history		*create_history_entry(char *line)
{
	t_history *new;

	if (line && ft_strcmp(line, "\n"))
	{
		new = (t_history *)memalloc_or_die(sizeof(t_history));
		new->line = ft_strdup(line);
		new->appended = false;
		new->next = NULL;
		new->prev = NULL;
		return (new);
	}
	return (NULL);
}
