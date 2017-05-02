# include "event_callback_def.h"
# include <libft.h>

void		move_cursor(t_vec2i	vec, t_term *term)
{
	if (vec.x > 0)
	{
		while (vec.x-- > 0)
			ft_putstr(term->move_left);
	}
	else if (vec.x < 0)
	{
		while (vec.x++ < 0)
			ft_putstr(term->move_right);
	}
	if (vec.y > 0)
	{
		while (vec.y-- > 0)
			ft_putstr(term->move_up);
	}
	else if (vec.y < 0)
	{
		while (vec.y++ < 0)
			ft_putstr(term->move_down);
	}
}

EV_CB_RET 	event_cursor_left(EV_CB_ARGS)
{
	t_vec2i		cursor_vec;
	t_vec2i		mov_vec;

	if (ed->cursor_position > 0)
	{
		ed->need_refresh = true;
		cursor_vec = get_cursor_vector(ed);
		ed->cursor_position--;
		mov_vec = vec2i_sub(cursor_vec, get_cursor_vector(ed));
		move_cursor(mov_vec, ed->term);
		ed->pos = get_cursor_vector(ed);
	}
}

EV_CB_RET 	event_cursor_right(EV_CB_ARGS)
{
	t_vec2i		cursor_vec;
	t_vec2i		mov_vec;

	if (ed->cursor_position < ed->string_size)
	{
		ed->need_refresh = true;
		cursor_vec = get_cursor_vector(ed);
		ed->cursor_position++;
		mov_vec = vec2i_sub(cursor_vec, get_cursor_vector(ed));
		move_cursor(mov_vec, ed->term);
		ed->pos = get_cursor_vector(ed);
	}
}

void move_cursor_to(t_vec2i old_pos, t_vec2i new_pos, t_term *term)
{
	move_cursor(vec2i_sub(old_pos, new_pos), term);
}
