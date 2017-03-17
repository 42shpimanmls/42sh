# include <libft.h>
# include "utils.h"
# include "abstract_list.h"
# include "read_input/editor/editor.h"
# include "read_input/event_callbacks/event_callback_def.h"
# include "read_input/termcap/init_deinit.h"

char *edit_input()
{
	//TERMCAPS
	char		*line;
	t_editor	*ed;

	ft_start_termcaps();
	ed = init_editor();

	char						buf[EVENT_STR_MAX_LEN + 1];
	ssize_t						ret;
	t_event_callback_def const	*def;

	while ((ret = read(0, buf, EVENT_STR_MAX_LEN)) > 0)
	{
		buf[ret] = '\0';
		def = get_matching_event_callback(buf);
		if (def)
		{
			if (def->id == NEWLINE_EVID)
			{
				break ;
			}
			else
			{
				def->callback(ed);
			}
		}
		else
		{
			if (ft_isprint(buf[0]))
			{
				add_to_string(&ed->string, buf[0]);
				ed->need_refresh = true;
			}
		}
		if (ed->need_refresh == true)
		{
			ed->need_refresh = false;
			ft_clear_line(ed->string);
			line = get_string_from_list(ed->string);
			ft_putstr(line);
			free(line);
		}
	}
	
	ft_close_termcaps();
	line = get_string_from_list(ed->string);
	free_string(ed->string);
	return (line);	
}
