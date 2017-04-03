# include <libft.h>
# include "read_input/event_callbacks/event_callback_def.h"

void clear_line(t_editor *ed)
{
	move_start(ed);
	ft_putstr(ed->term->clear_line);
	ed->pos = get_cursor_vector(ed);
}

void free_editor(t_editor *ed)
{
	free_string(ed->string);
	free(ed->prompt);
}
