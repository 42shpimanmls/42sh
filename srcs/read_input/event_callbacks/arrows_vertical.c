# include "event_callback_def.h"
# include <libft.h>

EV_CB_RET 	event_cursor_up(EV_CB_ARGS)
{
	t_vec2i pos;

	if (if_on_multiline(ed))
		return ;
	ed->need_refresh = true;

	pos = get_cursor_vector(ed);
	ed->cursor_position = find_index_at_vector(ed, pos.x, pos.y - 1);
	move_cursor_to(pos, get_cursor_vector(ed), ed->term);
	ed->pos = get_cursor_vector(ed);
}

EV_CB_RET 	event_cursor_down(EV_CB_ARGS)
{
	t_vec2i pos;

	if (if_on_multiline(ed))
		return ;

	ed->need_refresh = true;
	pos = get_cursor_vector(ed);
	ed->cursor_position = find_index_at_vector(ed, pos.x, pos.y + 1);
	move_cursor_to(pos, get_cursor_vector(ed), ed->term);
	ed->pos = get_cursor_vector(ed);
}
