#include "read_input/editor/editor.h"
#include <libft.h>

void put_highlighted_line(t_editor *ed, char* line)
{
	size_t	i;

	i = -1;
	if (!line || ft_strlen(line) <= 0)
		return ;
	while (line[++i])
	{
		if ((ed->selected_string_start > 0 || ed->selected_string_end > 0) &&
			((i >= ed->selected_string_start && i <= ed->selected_string_end) ||
			(i >= ed->selected_string_end && i <= ed->selected_string_start)))
			ft_putcharc(4, 3, line[i]);
		else
			ft_putchar(line[i]);
	}
}
