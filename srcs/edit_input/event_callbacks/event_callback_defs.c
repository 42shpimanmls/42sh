#include <stdlib.h>
#include "event_callback_def.h"
#include "uint.h"

t_event_callback_def const			*get_event_callback_defs(void)
{
	static t_event_callback_def const defs[EVENT_CALLBACK_DEF_COUNT] =
	{
		{ CURSOR_RIGHT_EVID, "CURSOR_RIGHT", "\x1b\x5b\x43", event_cursor_right},
	};
	return (defs);
}

t_event_callback_def const			*get_matching_event_callback(
	char const *str)
{
	(void)str;
	return (NULL);
}
