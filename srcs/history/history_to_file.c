#include "shell_env.h"
#include "history.h"

/*
**	-a appends if file exists
**	-w overwrites or creates file
**	if filename is specified, -w writes to file but -a does NOTHING
*/

void	hist_to_file(t_history *history, char *filename, bool append)
{
	int		fd;

	if (append)
		fd = open(HISTFILE, O_WRONLY | O_APPEND); // protect
	else
		fd = open(filename, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd > 0)
	{
		while (history)
		{
			if (!history->appended)
			{
				history->appended = true;
				ft_putstr_fd(history->line, fd);
			}
			history = history->next;
		}
		close(fd);
	}
	// set_error
}
