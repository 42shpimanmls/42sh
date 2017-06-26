#include <libft.h>
#include "read_input/event_callbacks/event_callback_def.h"

bool		if_on_multiline(t_editor *ed)
{
	char	*str;
	int		nb;

	str = get_string_from_list(ed->string);
	nb = ft_count_char(str, '\n');
	free(str);
	if (nb > 1)
		return (true);
	return (false);
}
