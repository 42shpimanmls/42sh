#include "event_callback_def.h"
#include "history/history.h"
#include "abstract_list.h"
#include <libft.h>

/** general functions that can be moved/reused  **/

void	list_free(t_abstract_list **list)
{
	if ((*list) && (*list)->next)
		list_free(&(*list)->next);
	free(*list);
	*list = NULL;
}

static void	str_to_list(t_editor *ed, char *str)
{
	if (str == NULL)
		return;
	while (*str)
	{
		add_to_string(ed, *str);
		str++;
	}
}

/***************************************/

static void change_string(EV_CB_ARGS, char *line)
{
	char	*trimed;

	clear_selected_pos(ed);
	list_free((t_abstract_list **)&ed->string);
	trimed = ft_strtrim(line);
	str_to_list(ed, trimed);
	ed->string_size = list_count((t_abstract_list *)ed->string);
	ed->cursor_position = ed->string_size;
	free(trimed);
}

EV_CB_RET 	event_history_up(EV_CB_ARGS)
{
	if (!ed->in_history)
	{
		ed->history_current = ed->history;
		ed->history_saved_current_string = get_string_from_list(ed->string);
	}
	if (ed->history_current && ed->history_current->prev)
	{
		ed->in_history = true;
		ed->need_refresh = true;

		if (ed->history_current != ed->history)
			ed->history_current = ed->history_current->prev;

		change_string(ed, ed->history_current->line);

		if (ed->history_current && ed->history_current == ed->history)
			ed->history_current = ed->history_current->prev;
	}
}

EV_CB_RET 	event_history_down(EV_CB_ARGS)
{
	if (!ed->in_history)
	{
		ed->history_current = ed->history;
		ed->history_saved_current_string = get_string_from_list(ed->string);
	}
	if (ed->history_current)
	{
		ed->in_history = true;
		ed->need_refresh = true;

		if (ed->history_current)
			ed->history_current = ed->history_current->next;

		if (ed->history_current)
		{
			change_string(ed, ed->history_current->line);
		}
		else
		{
			// change_string(ed, "base");
			change_string(ed, ed->history_saved_current_string);
			ed->in_history = false;
			ed->history_current = NULL;
		}
	}
}
