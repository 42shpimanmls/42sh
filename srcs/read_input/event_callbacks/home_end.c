#include "event_callback_def.h"
#include <libft.h>

EV_CB_RET 	event_cursor_home(EV_CB_ARGS)
{
	t_vec2i		pos;

	ed->need_refresh = true;
	pos = get_cursor_vector(ed);
	ed->cursor_position = 0;
	move_cursor_to(pos, get_cursor_vector(ed), ed->term);
	ed->pos = get_cursor_vector(ed);
}

EV_CB_RET 	event_cursor_end(EV_CB_ARGS)
{
	t_vec2i		pos;

	ed->need_refresh = true;
	pos = get_cursor_vector(ed);
	ed->cursor_position = ed->string_size;
	move_cursor_to(pos, get_cursor_vector(ed), ed->term);
	ed->pos = get_cursor_vector(ed);
}
