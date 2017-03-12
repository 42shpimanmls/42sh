#include <stdlib.h>
#include "event_callback_def.h"
#include "uint.h"

static t_event_callback_def const
	g_event_callback_defs[EVENT_CALLBACK_DEF_COUNT] =
{
	{ CURSOR_RIGHT_EVID, "CURSOR_RIGHT", "\x1b\x5b\x43", event_cursor_right},
};

t_event_callback_def const			*get_event_callback_defs(void)
{
	return (g_event_callback_defs);
}

t_event_callback_def const			*get_matching_event_callback(
	char const *str)
{
	(void)str;
	return (NULL);
}
