#include "event_callback_def.h"
#include <libft.h>

bool check_cursor_if_margin_right(EV_CB_ARGS)
{
	int md = (ed->cursor_position + 1 + ed->prompt_size) % ed->term->width;
	if (md == 0)
		return (true);
	return (false);
}

bool check_cursor_if_margin_left(EV_CB_ARGS)
{
	int md = (ed->cursor_position + ed->prompt_size) % ed->term->width; 
	if (md == 0)
		return (true);
	return (false);
}

EV_CB_RET 	event_cursor_left(EV_CB_ARGS)
{
	(void)ed;
	// ed->need_refresh = true;
	if (ed->cursor_position > 0)
	{
		if (check_cursor_if_margin_left(ed))
		{
			ft_putstr(ed->term->move_up);
			int i = -1;
			while (++i != ed->term->width)
				ft_putstr(ed->term->move_right);
		}
		else
		{
			ft_putstr(ed->term->move_left);
		}
		ed->cursor_position--;
	}
}

EV_CB_RET 	event_cursor_right(EV_CB_ARGS)
{
	(void)ed;
	// ed->need_refresh = true;
	if (ed->cursor_position < ed->string_size)
	{
		if (check_cursor_if_margin_right(ed))
		{
			ft_putstr(ed->term->move_down);
			ft_putstr(ed->term->move_cursor_begining);
		}
		else
		{
			ft_putstr(ed->term->move_right);
		}
		ed->cursor_position++;		
	}
}

EV_CB_RET 	event_cursor_up(EV_CB_ARGS)
{(void)ed;}

EV_CB_RET 	event_cursor_down(EV_CB_ARGS)
{(void)ed;}
