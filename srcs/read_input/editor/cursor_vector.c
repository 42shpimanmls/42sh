#include <libft.h>
#include "editor.h"

size_t		find_index_at_vector(t_editor *ed, int ox, int oy)
{
	char	*str;
	int		i;
	t_vec2i	vec;

	str = get_string_from_list(ed->string);
	vec.x = ed->prompt_size;
	vec.y = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (vec.y > oy || (vec.y == oy && vec.x >= ox))
			break ;
		if (vec.x >= ed->term->width - 1 || str[i] == '\n')
		{
			vec.y++;
			if (vec.x >= ed->term->width - 1 && str[i] == '\n')
				vec.y++;
			vec.x = 0;
		}
		else
			vec.x++;
		i++;
	}
	return (i);
}

t_vec2i		get_cursor_vector(t_editor *ed)
{
	char			*str;
	size_t			i;
	t_vec2i			vec;

	str = get_string_from_list(ed->string);
	vec.x = ed->prompt_size;
	vec.y = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (i == ed->cursor_position)
			break ;
		if (vec.x >= ed->term->width - 1 || str[i] == '\n')
		{
			vec.y++;
			if (vec.x >= ed->term->width - 1 && str[i] == '\n')
				vec.y++;
			vec.x = 0;
		}
		else
			vec.x++;
		i++;
	}
	return (vec);
}
