#include "shell_env.h"
#include "history.h"
#include "errors.h"
#include "utils.h"

void		free_history(t_history **history)
{
	ft_strdel(&(*history)->line);
	free(*history);
	*history = NULL;
}

void		delete_history_entry(t_history **history, char *offset) // change entirely
{
	t_history *tmp;
	int		n_offset;

	tmp = *history;
	if (str_is_digits(offset))
	{
		n_offset = ft_atoi(offset);
		while (n_offset > 1 && tmp)
		{
			tmp = tmp->next;
			n_offset--;
		}
			if (!tmp || n_offset <= 0)
				error_builtin("history", offset, OUT_OF_RANGE);
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
	else
		error_builtin("history", offset, OUT_OF_RANGE);
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