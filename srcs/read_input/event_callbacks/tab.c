#include "event_callback_def.h"
#include "abstract_list.h"
#include "completion.h"
#include <libft.h>

EV_CB_RET	ev_tab(t_editor *ed)
{
	char *line;
	char *path;

	if (ed->in_selection)
		return ;
	line = get_string_from_list(ed->string);
	while (line[ed->cursor_position] != ' ' && line[ed->cursor_position])
		ev_cursor_right(ed);
	path = get_cur_word(ed->cursor_position, line);
	choice_tab(ed, line, path);
	ft_strdel(&line);
}
