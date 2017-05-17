#include "event_callback_def.h"

EV_CB_RET	ev_paste(t_editor *ed)
{
	size_t i;

	i = -1;
	if (ed->selected_string)
	{
		ed->pos = get_cursor_vector(ed);
		while (ed->selected_string[++i])
		{
			add_to_string(ed, ed->selected_string[i]);
		}
	}
}
