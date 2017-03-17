#include "event_callback_def.h"
#include "history.h"
#include <libft.h>

EV_CB_RET 	event_history_up(EV_CB_ARGS)
{
	if (ed->history->prev)
	{
		ed->history = ed->history->prev;
	}
}

EV_CB_RET 	event_history_down(EV_CB_ARGS)
{
	if (ed->history->next)
	{
		ed->history = ed->history->next;
	}
}
