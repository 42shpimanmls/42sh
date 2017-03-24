# include <libft.h>
# include "utils.h"
# include "abstract_list.h"
# include "read_input/editor/editor.h"
# include "read_input/event_callbacks/event_callback_def.h"
# include "read_input/termcap/init_deinit.h"

void move_start(t_editor *ed)
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

void restore_old_cursor_position(t_vec2i old_pos, t_vec2i new_pos, t_term *term)
{
	move_cursor(vec2i_sub(old_pos, new_pos), term);
}

#include <stdio.h>

void print_command_string(char const *prompt, t_string *cmd_str
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
	u = 0;
	while (lines[u] != NULL)
	{
		ft_putstr(lines[u]);
		if (ft_strlen(lines[u]) % term_width == 0)
			ft_putchar('\n');
		if (lines[u + 1] != NULL)
			ft_putchar('\n');
		u++;
	}
}

void refresh_line(t_editor *ed)
{
	t_vec2i	tmp;
	int		save;
	char	*line;

	if (ed->need_refresh == true)
	{
		ed->need_refresh = false;
		move_start(ed);
		ft_putstr(ed->term->clear_line);
		tmp = get_cursor_vector(ed);
		print_command_string(ed->prompt, ed->string, ed->term->width);
		line = get_string_from_list(ed->string);
		save = ed->cursor_position;
		ed->cursor_position = ft_strlen(line);
		free(line);
		restore_old_cursor_position(get_cursor_vector(ed), tmp, ed->term);
		ed->cursor_position = save;
	}
}

void free_editor(t_editor *ed)
{
	free_string(ed->string);
	free(ed->prompt);
}

char *edit_input()
{
	char						buf[EVENT_STR_MAX_LEN + 1];
	ssize_t						ret;
	t_event_callback_def const	*def;
	t_editor					*ed;
	char						*line;

	ft_start_termcaps();
	ed = get_editor();
	init_editor();
	ed->need_refresh = true;
	refresh_line(ed);

	while ((ret = read(0, buf, EVENT_STR_MAX_LEN)) > 0)
	{
		dprintf(2, "cursor_pos\n");
		print_vec2i(get_cursor_vector(ed), 2);
		buf[ret] = '\0';
		def = get_matching_event_callback(buf);
		if (def)
		{
			def->callback(ed);
			if (def->id == NEWLINE_EVID)
				break ;
		}
		else
		{
			if (ft_isprint(buf[0]))
				add_to_string(ed, buf[0]);
		}
		refresh_line(ed);
		dprintf(2, "cursor_pos\n");
		print_vec2i(get_cursor_vector(ed), 2);
	}

	ft_close_termcaps();
	line = get_string_from_list(ed->string);
	free_editor(ed);
	return (line);
}
