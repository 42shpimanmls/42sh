#include "event_callback_def.h"
#include <libft.h>

EV_CB_RET 	event_cursor_home(EV_CB_ARGS)
{
	t_vec2i		cursor_vec;
	t_vec2i		mov_vec;

	cursor_vec = get_cursor_vector(ed);
	ed->cursor_position = 0;
	mov_vec = vec2i_sub(cursor_vec, get_cursor_vector(ed));
	move_cursor(mov_vec, ed->term);
}

EV_CB_RET 	event_cursor_end(EV_CB_ARGS)
{
	clear_line(ed);
	ed->cursor_position = ed->string_size;
	put_line(ed);
}
