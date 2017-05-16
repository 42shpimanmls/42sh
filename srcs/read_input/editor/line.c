#include <libft.h>
#include "read_input/event_callbacks/event_callback_def.h"
#include "abstract_list.h"

void		move_start(t_editor *ed)
{
	while (ed->pos.y-- > 0)
		ft_putstr(ed->term->move_up);
	ft_putstr(ed->term->move_cursor_begining);
}

static void	print_command_string(t_editor *ed, char const *prompt,
		t_string *cmd_str, size_t term_width)
{
	char	*str;

	str = ft_strjoinf(prompt, get_string_from_list(cmd_str), 2);
	put_highlighted_line(ed, str);
	if (ft_strlen(str) % (int)term_width == 0 && !if_on_multiline(ed))
		ft_putchar('\n');
	free(str);
}

void		put_line(t_editor *ed)
{
	char		*line;

	ed->string_size = list_count((t_abstract_list *)ed->string);
	print_command_string(ed, ed->prompt, ed->string, ed->term->width);
	line = get_string_from_list(ed->string);
	ed->old_position = ed->cursor_position;
	ed->cursor_position = ft_strlen(line);
	free(line);
}

void		restore_old_cursor_position(t_editor *ed, t_vec2i old_pos)
{
	move_cursor(vec2i_sub(old_pos, ed->pos), ed->term);
	ed->cursor_position = ed->old_position;
}

void		refresh_line(t_editor *ed)
{
	if (ed->need_refresh == true)
	{
		ed->need_refresh = false;
		ft_putstr(ed->term->hide_cursor);
		clear_line(ed);
		put_line(ed);
		restore_old_cursor_position(ed, get_cursor_vector(ed));
		ft_putstr(ed->term->show_cursor);
	}
}
