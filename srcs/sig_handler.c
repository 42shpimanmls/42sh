#include "sig_handler.h"
#include "ftsh.h"
#include "read_input/editor/editor.h"
#include "errno.h"
#include <sys/wait.h>

void		sig_handler(int sig)
{
	t_editor	*ed;
	t_shell_env	*shell_env;

	ed = get_editor();
	shell_env = get_shell_env();
	if (sig == SIGINT)
	{
		if (shell_env->last_unmatched)
		{
			set_error(NO_ERROR);
			shell_env->last_unmatched = 0;
			ft_strdel(&shell_env->input_string);
			clear_line(ed);
			while (shell_env->should_run)
				main_loop();
		}
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