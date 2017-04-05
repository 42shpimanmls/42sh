# include <libft.h>
# include "read_input/event_callbacks/event_callback_def.h"
# include "abstract_list.h"

// void		print_cursor_vector(t_editor *ed);

void move_start(t_editor *ed)
{
	t_vec2i	vec;

	vec = get_cursor_vector(ed);
	// print_cursor_vector(ed);

	if (vec.x > 0)
	{
		while (vec.y-- > 0)
			ft_putstr(ed->term->move_up);
	}
	else
	{
		while (vec.y-- > 1)
			ft_putstr(ed->term->move_up);
	}
	ft_putstr(ed->term->move_cursor_begining);
}

static void print_command_string(t_editor *ed, char const *prompt, t_string *cmd_str
	, size_t term_width)
{
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

void put_line(t_editor *ed)
{
	char		*line;

	ed->string_size = list_count((t_abstract_list *)ed->string);
	print_command_string(ed, ed->prompt, ed->string, ed->term->width);
	line = get_string_from_list(ed->string);
	ed->old_position = ed->cursor_position;
	ed->cursor_position = ft_strlen(line);
	free(line);
}

static void restore_old_cursor_position(t_editor *ed, t_vec2i old_pos)
{
	move_cursor(vec2i_sub(old_pos, ed->pos), ed->term);
}

void refresh_line(t_editor *ed)
{
	if (ed->need_refresh == true)
	{
		ed->need_refresh = false;
		ft_putstr(ed->term->hide_cursor);
		clear_line(ed);
		put_line(ed);
		restore_old_cursor_position(ed, get_cursor_vector(ed));
		ed->cursor_position = ed->old_position;
		ft_putstr(ed->term->show_cursor);
	}
}