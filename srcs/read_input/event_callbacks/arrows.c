#include "event_callback_def.h"
#include <libft.h>

EV_CB_RET 	event_cursor_left(EV_CB_ARGS)
{
	(void)ed;
	ft_putstr(ed->term->move_left);
}

EV_CB_RET 	event_cursor_right(EV_CB_ARGS)
{
	(void)ed;
	ft_putstr(ed->term->move_right);
}

EV_CB_RET 	event_cursor_up(EV_CB_ARGS)
{(void)ed;}

EV_CB_RET 	event_cursor_down(EV_CB_ARGS)
{(void)ed;}
