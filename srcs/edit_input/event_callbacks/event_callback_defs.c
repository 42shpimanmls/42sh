#include <stdlib.h>
#include "event_callback_def.h"
#include "uint.h"
#include "libft.h"

t_event_callback_def const			*get_event_callback_defs(void)
{
	static t_event_callback_def const defs[EVENT_CALLBACK_DEF_COUNT] =
	{
	//	ID							ID_STR					MATCHING STR		HANDLER FUNCTION
		{ NEWLINE_EVID,				"NEWLINE",				"\n",				NULL },
		{ HISTORY_UP_EVID,			"HISTORY_UP",			"\x1b[A",			NULL },
		{ HISTORY_DOWN_EVID,		"HISTORY_DOWN",			"\x1b[B",			NULL },
		{ CURSOR_RIGHT_EVID, 		"CURSOR_RIGHT",			"\x1b[C",			event_cursor_right },
		{ CURSOR_LEFT_EVID, 		"CURSOR_LEFT",			"\x1b[D",			NULL },
		{ CURSOR_UP_EVID, 			"CURSOR_UP",			"\x1b[1;5A",		NULL },
		{ CURSOR_DOWN_EVID,			"CURSOR_DOWN",			"\x1b[1;5B",		NULL },
		{ CURSOR_WORD_RIGHT_EVID,	"CURSOR_WORD_RIGHT",	"\x1b[1;5C",		NULL },
		{ CURSOR_WORD_LEFT_EVID,	"CURSOR_WORD_LEFT",		"\x1b[1;5D",		NULL },
		{ CURSOR_HOME_EVID,			"CURSOR_HOME",			"\x1b[H",			NULL },
		{ CURSOR_END_EVID,			"CURSOR_END",			"\x1b[F",			NULL },
		{ COPY_EVID,				"COPY",					"\x2",				NULL },
		{ CUT_EVID,					"CUT",					"\xb",				NULL },
		{ PASTE_EVID,				"PASTE",				"\x10",				NULL },
		{ CANCEL,					"CANCEL",				"\x3",				NULL },
		{ EXIT,						"EXIT",					"\x4",				NULL },
		{ DELETE,					"DELETE",				"\x7f",				NULL }
	};
	return (defs);
}

t_event_callback_def const			*get_matching_event_callback(
	char const *str)
{
	t_uint						u;
	t_event_callback_def const	*defs;

	defs = get_event_callback_defs();
	u = 0;
	while (u < EVENT_CALLBACK_DEF_COUNT)
	{
		if (defs[u].str != NULL && ft_strncmp(defs[u].str, str, ft_strlen(defs[u].str)) == 0)
			return (defs + u);
		u++;
	}
	return (NULL);
}
