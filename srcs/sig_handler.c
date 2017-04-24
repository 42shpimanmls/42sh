#include "sig_handler.h"
#include "ftsh.h"
#include "read_input/editor/editor.h"
#include "errno.h"
#include <sys/wait.h>

void		sig_handler(int sig)
{
	t_editor	*ed;

	ed = get_editor();
	if (sig == SIGINT)
	{
		init_editor();
		refresh_line(ed);
		wait(0);
		if (errno == ECHILD)
		{
			ft_putchar('\n');
			put_line(ed);
		}
	}
}