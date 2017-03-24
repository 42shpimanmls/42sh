#include "event_callback_def.h"
#include <libft.h>

size_t		find_index_at_vector(t_editor *ed, int ox, int oy)
{
	char	*str;
	int		i;
	t_vec2i	vec;

	str = get_string_from_list(ed->string);
	vec.x = ed->prompt_size;
	vec.y = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((vec.y >= oy && vec.x >= ox))
			break ;
		if (vec.x == ed->term->width - 1 || str[i] == '\n')
		{
			vec.x = 0;
			vec.y++;
		}
		else
			vec.x++;
		i++;
	}
	return (i);
}

t_vec2i		get_cursor_vector(t_editor *ed)
{
	char	*str;
	int		i;
	t_vec2i	vec;

	str = get_string_from_list(ed->string);
	vec.x = ed->prompt_size;
	vec.y = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (i == ed->cursor_position)
			break ;
		if (vec.x == ed->term->width - 1 || str[i] == '\n')
		{
			vec.x = 0;
			vec.y++;
		}
		else
			vec.x++;
		i++;
	}
	return (vec);
}

t_vec2i		vec2i_sub(t_vec2i a, t_vec2i b)
{
	t_vec2i	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return (result);
}

void		move_cursor(t_vec2i	vec, t_term *term)
{
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
}

EV_CB_RET 	event_cursor_left(EV_CB_ARGS)
{
	t_vec2i		cursor_vec;
	t_vec2i		mov_vec;

	if (ed->cursor_position > 0)
	{
		cursor_vec = get_cursor_vector(ed);
		ed->cursor_position--;
		mov_vec = vec2i_sub(cursor_vec, get_cursor_vector(ed));
		move_cursor(mov_vec, ed->term);
	}
}

EV_CB_RET 	event_cursor_right(EV_CB_ARGS)
{
	t_vec2i		cursor_vec;
	t_vec2i		mov_vec;

	if (ed->cursor_position < ed->string_size)
	{
		cursor_vec = get_cursor_vector(ed);
		ed->cursor_position++;
		mov_vec = vec2i_sub(cursor_vec, get_cursor_vector(ed));
		move_cursor(mov_vec, ed->term);
	}
}

void move_cursor_to(t_vec2i old_pos, t_vec2i new_pos, t_term *term)
{
	move_cursor(vec2i_sub(old_pos, new_pos), term);
}

EV_CB_RET 	event_cursor_up(EV_CB_ARGS)
{
	t_vec2i pos;

	pos = get_cursor_vector(ed);
	ed->cursor_position = find_index_at_vector(ed, pos.x, pos.y - 1);
	move_cursor_to(pos, get_cursor_vector(ed), ed->term);
}

EV_CB_RET 	event_cursor_down(EV_CB_ARGS)
{
	t_vec2i pos;

	pos = get_cursor_vector(ed);
	ed->cursor_position = find_index_at_vector(ed, pos.x, pos.y + 1);
	move_cursor_to(pos, get_cursor_vector(ed), ed->term);
}
