#include "event_callback_def.h"

void restore_old_cursor_position(t_editor *ed, t_vec2i old_pos);
void		print_cursor_vector(t_editor *ed);

EV_CB_RET	event_paste(EV_CB_ARGS)
{
	size_t i;

	if (if_on_multiline(ed))
		return ;
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
