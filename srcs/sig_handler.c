#include "sig_handler.h"
#include "ftsh.h"
#include "read_input/editor/editor.h"
#include "errno.h"

void		sig_handler(int sig)
{
	t_editor	*ed;

	ed = get_editor();
	if (sig == SIGINT)
	{
		ft_putchar('\n');
		init_editor();
		wait(0);
		refresh_line(ed);
		if (errno == ECHILD)
			put_line(ed);
	}
}