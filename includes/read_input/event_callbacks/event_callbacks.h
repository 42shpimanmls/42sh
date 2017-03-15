#ifndef EVENT_CALLBACK
# define EVENT_CALLBACK

/*# include "editor.h"*/

# define EV_CB_RET void
# define EV_CB_ARGS /*t_editor ed*/

typedef EV_CB_RET	(*t_event_callback)(EV_CB_ARGS);

EV_CB_RET 	event_cursor_right(EV_CB_ARGS);

#endif
