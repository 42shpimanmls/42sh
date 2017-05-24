#include "event_callback_def.h"
#include "history/history_def.h"
#include "abstract_list.h"
#include "utils.h"
#include <libft.h>

/*
** general functions that can be moved/reused
*/

static void	str_to_list_in_editor(t_editor *ed, char *str)
{
	if (str == NULL)
		return ;
	while (*str)
	{
		add_to_string(ed, *str);
		str++;
	}
}

/*
**********************************************
*/

static void	change_string(t_editor *ed, char *line)
{
	char	*trimed;

	clear_selected_pos(ed);
	list_free((t_abstract_list **)&ed->string);
	trimed = ft_strtrim(line);
	str_to_list_in_editor(ed, trimed);
	ed->string_size = list_count((t_abstract_list *)ed->string);
	ed->cursor_position = ed->string_size;
	free(trimed);
}

void		close_history(t_editor *ed)
{
	free(ed->history_saved_current_string);
	ed->history_saved_current_string = NULL;
	ed->in_history = false;
	ed->history_current = NULL;
}

EV_CB_RET	ev_history_up(t_editor *ed)
{
	if (!ed->in_history)
	{
		ed->history_current = ed->history;
		ed->history_saved_current_string = get_string_from_list(ed->string);
	}
	else if (ed->history_current->prev)
	{
		ed->history_current = ed->history_current->prev;
	}
	if (ed->history_current)
	{
		ed->in_history = true;
		ed->need_refresh = true;
		change_string(ed, ed->history_current->line);
	}
}

EV_CB_RET	ev_history_down(t_editor *ed)
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
			change_string(ed, ed->history_saved_current_string);
			close_history(ed);
		}
	}
}
