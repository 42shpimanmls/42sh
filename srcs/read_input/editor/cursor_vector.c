#include <libft.h>
#include "editor.h"

size_t		find_index_at_vector(t_editor *ed, int ox, int oy)
{
	char	*str;
	size_t	i;
	t_vec2i	vec;

	str = ft_strjoinf(ed->prompt, get_string_from_list(ed->string), 2);
	vec.x = 0;
	vec.y = 0;
	i = 0;
	while (i < ed->prompt_size || str[i - ed->prompt_size] != '\0')
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
	free(str);
	return (i - ed->prompt_size);
}

t_vec2i		get_cursor_vector(t_editor *ed)
{
	char			*str;
	size_t			i;
	t_vec2i			vec;

	str = ft_strjoinf(ed->prompt, get_string_from_list(ed->string), 2);
	vec.x = 0;
	vec.y = 0;
	i = 0;
	while (i < ed->prompt_size || str[i - ed->prompt_size] != '\0')
	{
		if (i >= ed->cursor_position + ed->prompt_size)
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
	free(str);
	return (vec);
}
