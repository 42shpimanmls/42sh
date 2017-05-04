#include <libft.h>
#include <signal.h>
#include "read_input/editor/editor.h"
#include "read_input/event_callbacks/event_callback_def.h"
#include "read_input/termcap/init_deinit.h"
#include "read_input/edit_input.h"

void	refresh_termcap(int ret)
{
	t_editor *ed;

	(void)ret;
	ed = get_editor();
	if (!ed || !ed->in_edition)
		return ;
	ft_close_termcaps();
	ft_start_termcaps();
	free(ed->term);
	ed->term = NULL;
	ed->term = init_term();
	ed->pos = get_cursor_vector(ed);
}

char	*edit_input(void)
{
	t_editor	*ed;
	char		*line;

	signal(SIGWINCH, refresh_termcap);
	ft_start_termcaps();
	ed = get_editor();
	init_editor();
	if (ed->term->rescue_mode)
	{
		line = start_rescue_mode();
	}
	else
	{
		ed->in_edition = true;
		line = start_normal_mode(ed);
	}
	ed->in_edition = false;
	free_editor(ed);
	return (line);
}
