#include "shell_env.h"
#include "history.h"

void	hist_to_file(t_history *history, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDWR | O_CREAT, 0666);
	while(ft_get_next_line(fd, &line))
		ft_strdel(&line);
	while (history)
	{
		if (!history->appended) // || option is -w not -a
		{
			history->appended = true;
			ft_putendl_fd(history->line, fd);
		}
		history = history->next;
	}	
}