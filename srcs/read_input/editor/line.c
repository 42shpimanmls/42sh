# include <libft.h>
# include "read_input/event_callbacks/event_callback_def.h"

void move_start(EV_CB_ARGS)
{
	t_vec2i	vec;

	vec = get_cursor_vector(ed);
	while (vec.y > 0)
	{
		ft_putstr(ed->term->move_up);
		vec.y--;
	}
	ft_putstr(ed->term->move_cursor_begining);
}

static void print_command_string(EV_CB_ARGS, char const *prompt, t_string *cmd_str
	, size_t term_width)
{
	(void)term_width;
	char	**lines;
	char	*str;
	char	*tmp;
	size_t	u;

	tmp = get_string_from_list(cmd_str);
	str = ft_strjoin(prompt, tmp);
	free(tmp);
	lines = ft_strsplit(str, '\n');
	free(str);
	u = 0;
	while (lines[u] != NULL)
	{
		put_highlighted_line(ed, lines[u]);
		if (ft_strlen(lines[u]) % term_width == 0)
			ft_putchar('\n');
		if (lines[u + 1] != NULL)
			ft_putchar('\n');
		u++;
	}
	ft_freetabchar(lines);
}

void put_line(EV_CB_ARGS)
{
	char		*line;

	print_command_string(ed, ed->prompt, ed->string, ed->term->width);
	line = get_string_from_list(ed->string);
	ed->old_position = ed->cursor_position;
	ed->cursor_position = ft_strlen(line);
	free(line);
}

static void restore_old_cursor_position(EV_CB_ARGS, t_vec2i old_pos)
{
	move_cursor(vec2i_sub(old_pos, ed->pos), ed->term);
}

void refresh_line(EV_CB_ARGS)
{
	if (ed->need_refresh == true)
	{
		ed->need_refresh = false;
		clear_line(ed);
		put_line(ed);
		restore_old_cursor_position(ed, get_cursor_vector(ed));
		ed->cursor_position = ed->old_position;
	}
}
