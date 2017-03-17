#include "event_callback_def.h"
#include <libft.h>

EV_CB_RET 	event_newline(EV_CB_ARGS)
{(void)ed;}

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

EV_CB_RET 	event_cursor_home(EV_CB_ARGS)
{(void)ed;}

EV_CB_RET 	event_cursor_end(EV_CB_ARGS)
{(void)ed;}

EV_CB_RET 	event_cursor_word_right(EV_CB_ARGS)
{(void)ed;}

EV_CB_RET 	event_cursor_word_left(EV_CB_ARGS)
{(void)ed;}

EV_CB_RET 	event_history_up(EV_CB_ARGS)
{(void)ed;}

EV_CB_RET 	event_history_down(EV_CB_ARGS)
{(void)ed;}

EV_CB_RET 	event_copy(EV_CB_ARGS)
{(void)ed;}

EV_CB_RET 	event_cut(EV_CB_ARGS)
{(void)ed;}

EV_CB_RET 	event_paste(EV_CB_ARGS)
{(void)ed;}

EV_CB_RET 	event_cancel(EV_CB_ARGS)
{(void)ed;}

EV_CB_RET 	event_exit(EV_CB_ARGS)
{(void)ed;}

EV_CB_RET 	event_delete(EV_CB_ARGS)
{(void)ed;}

