# include "event_callback_def.h"
# include "abstract_list.h"
# include <libft.h>

EV_CB_RET 	event_newline(EV_CB_ARGS)
{
	ed->cursor_position = ed->string_size;
	add_to_string(ed, '\n');
	ft_putchar('\n');
}

EV_CB_RET 	event_cancel(EV_CB_ARGS)
{(void)ed;}

EV_CB_RET 	event_exit(EV_CB_ARGS)
{(void)ed;}

EV_CB_RET 	event_delete(EV_CB_ARGS)
{
	if (ed->cursor_position <= 0)
		return ;
	ed->need_refresh = true;
	event_cursor_left(ed);
	list_pop_at_pos(ed->cursor_position, (t_abstract_list **)&ed->string);
}

EV_CB_RET 	event_delete_right(EV_CB_ARGS)
{
	ed->need_refresh = true;
	list_pop_at_pos(ed->cursor_position, (t_abstract_list **)&ed->string);
}
