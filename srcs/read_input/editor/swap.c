# include "read_input/event_callbacks/event_callback_def.h"
# include <libft.h>

void 	swap_position_if_needed(EV_CB_ARGS)
{
	size_t tmp;

	if (ed->selected_string_start > ed->selected_string_end)
	{
		tmp = ed->selected_string_start;
		ed->selected_string_start = ed->selected_string_end;
		ed->selected_string_end = tmp;
	}
}
