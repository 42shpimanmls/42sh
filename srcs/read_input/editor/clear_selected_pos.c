# include "read_input/event_callbacks/event_callback_def.h"
# include <libft.h>

void clear_selected_pos(t_editor *ed)
{
	ed->in_selection = false;
	ed->selected_string_start = 0;
	ed->selected_string_end = 0;
}
