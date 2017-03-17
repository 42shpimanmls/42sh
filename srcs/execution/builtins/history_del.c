#include "shell_env.h"
#include "history.h"

void		free_history(t_history **history)
{
	ft_strdel(&(*history)->line);
	free(*history);
	*history = NULL;
}

void		delete_history_entry(t_history **history, int offset) // change entirely
{
	t_history *tmp;

	tmp = *history;
	while (offset > 1 && tmp)
	{
		tmp = tmp->next;
		offset--;
	}
	if (!tmp || offset <= 0)
		ft_putendl("insert history error (offset: history position out of range)");
	else
	{
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		if (tmp->prev)
			tmp->prev->next = tmp->next;
		else
			*history = tmp->next;
		free_history(&tmp);
	}
}

void		clear_history_list(t_history **history)
{
	if (*history)
	{
		if ((*history)->next)
			clear_history_list(&(*history)->next);
		free_history(history);
	}
}