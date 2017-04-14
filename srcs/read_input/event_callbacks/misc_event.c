# include "event_callback_def.h"
# include "abstract_list.h"
# include <libft.h>

EV_CB_RET 	event_newline(EV_CB_ARGS)
{
	event_cursor_end(ed);
	close_history(ed);
	add_to_string(ed, '\n');
	refresh_line(ed);
}

EV_CB_RET 	event_cancel(EV_CB_ARGS)
{(void)ed;}

EV_CB_RET 	event_exit(EV_CB_ARGS)
{(void)ed;}

EV_CB_RET 	event_delete(EV_CB_ARGS)
{
	void **p;

	if (ed->cursor_position <= 0)
		return ;
	ed->need_refresh = true;
	event_cursor_left(ed);
	p = list_pop_at_pos(ed->cursor_position, (t_abstract_list **)&ed->string);
	free(p);
}

EV_CB_RET 	event_delete_right(EV_CB_ARGS)
{
	void **p;

	ed->need_refresh = true;
	p = list_pop_at_pos(ed->cursor_position, (t_abstract_list **)&ed->string);
	free(p);
}
