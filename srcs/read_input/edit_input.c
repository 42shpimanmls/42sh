# include <libft.h>
# include "utils.h"
# include "abstract_list.h"
# include "read_input/editor/editor.h"
# include "read_input/event_callbacks/event_callback_def.h"
# include "read_input/termcap/init_deinit.h"

void move_start(t_editor *ed)
{
	ed->string_size = list_count((t_abstract_list*)ed->string);
	ed->prompt_size = ft_strlen(PROMPT);
	int size = ed->prompt_size + ed->cursor_position;

	while (size > ed->term->width + 1)
	{
		size -= ed->term->width;
		ft_putstr(ed->term->move_up);
	}
	ft_putstr(ed->term->move_cursor_begining);
}

void restore_old_cursor_position(t_editor *ed, int old_position)
{
	ed->cursor_position = ed->string_size;
	while (ed->cursor_position > old_position)
	{
		event_cursor_left(ed);
	}
}

void refresh_line(t_editor *ed)
{
	// ft_dprintf(2, "width   : %d\n", ed->term->width);
	// ft_dprintf(2, "position: %d\n", ed->cursor_position);
	// int md = (ed->cursor_position + ed->prompt_size) % ed->term->width;
	// ft_dprintf(2, "modulo: %d\n", md);
	// ft_dprintf(2, "---------------------------------\n");

	char		*line;

	if (ed->need_refresh == true)
	{
		ed->need_refresh = false;
		move_start(ed);
		ft_putstr(ed->term->clear_line);

		line = get_string_from_list(ed->string);
		ft_putstr(PROMPT);
		ft_putstr(line);
		free(line);
		restore_old_cursor_position(ed, ed->cursor_position);
	}
}

char *edit_input()
{
	//TERMCAPS
	char						buf[EVENT_STR_MAX_LEN + 1];
	ssize_t						ret;
	t_event_callback_def const	*def;
	t_editor					*ed;
	char						*line;

	ft_start_termcaps();
	ed = get_editor();
	ed->need_refresh = true;
	refresh_line(ed);

	while ((ret = read(0, buf, EVENT_STR_MAX_LEN)) > 0)
	{
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
			{
				add_to_string(ed, buf[0]);
			}
		}
		refresh_line(ed);
	}

	ft_close_termcaps();

	line = get_string_from_list(ed->string);
	free_string(ed->string);
	return (line);
}
