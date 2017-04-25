#ifndef EVENT_CALLBACKS_H
# define EVENT_CALLBACKS_H

# include "read_input/editor/editor.h"

# define EV_CB_RET void
# define EV_CB_ARGS t_editor *ed

typedef EV_CB_RET	(*t_event_callback)(t_editor *ed);

void	event_cursor_right(t_editor *ed);
void	event_newline(t_editor *ed);
void	event_cursor_left(t_editor *ed);
void	event_cursor_right(t_editor *ed);
void	event_cursor_up(t_editor *ed);
void	event_cursor_down(t_editor *ed);
void	event_cursor_home(t_editor *ed);
void	event_cursor_end(t_editor *ed);
void	event_cursor_word_right(t_editor *ed);
void	event_cursor_word_left(t_editor *ed);
void	event_history_up(t_editor *ed);
void	event_history_down(t_editor *ed);
void	event_copy(t_editor *ed);
void	event_cut(t_editor *ed);
void	event_paste(t_editor *ed);
void	event_cancel(t_editor *ed);
void	event_exit(t_editor *ed);
void	event_delete(t_editor *ed);
void	event_delete_right(t_editor *ed);

#endif
