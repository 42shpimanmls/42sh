#include "read_input/editor/editor.h"
#include <libft.h>

void put_highlighted_line(t_editor *ed, char* line)
{
	size_t	i;
	size_t	start;
	size_t	end;

	i = -1;
	if (!line || ft_strlen(line) <= 0)
		return ;
	start = ed->selected_string_start;
	end = ed->selected_string_end;

	while (line[++i])
	{
		if ((start > 0 || end > 0) &&
			((i >= start && i < end) || (i >= end && i < start)))
		{
			ft_putcharc(4, 3, line[i]);
		}
		else
			ft_putchar(line[i]);
	}
}
