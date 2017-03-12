#ifndef EVENT_CALLBACK_DEF_H
# define EVENT_CALLBACK_DEF_H

# include "bool.h"
# include "event_callbacks.h"

typedef enum				e_event_id
{
	CURSOR_RIGHT_EVID = 0
}							t_event_id;

typedef struct				s_event_callback_def
{
	t_event_id const		id;
	char const *const		name;
	char const *const		str;
	t_event_callback const	callback;
}							t_event_callback_def;

# define EVENT_CALLBACK_DEF_COUNT 1

t_event_callback_def const			*get_event_callback_defs(void);
t_event_callback_def const			*get_matching_event_callback(
	char const *str);

void								print_event_callback_def(
	t_event_callback_def const *def);
void								print_event_callback_defs(void);



#endif
