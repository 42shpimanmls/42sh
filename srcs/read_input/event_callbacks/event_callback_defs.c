#include <stdlib.h>
#include "event_callback_def.h"
#include "uint.h"
#include "libft.h"

t_event_callback_def const			*get_event_callback_defs(void)
{
	static t_event_callback_def const defs[EVENT_CALLBACK_DEF_COUNT] =
	{
	//	ID							ID_STR					MATCHING STR		HANDLER FUNCTION
		{ NEWLINE_EVID,				"NEWLINE",				"\n",				event_newline },
		{ CURSOR_LEFT_EVID, 		"CURSOR_LEFT",			"\x1b[D",			event_cursor_left },
		{ CURSOR_RIGHT_EVID, 		"CURSOR_RIGHT",			"\x1b[C",			event_cursor_right },
		{ CURSOR_UP_EVID, 			"CURSOR_UP",			"\x1b\x5b\x35\x7e",	event_cursor_up },
		{ CURSOR_UP_EVID, 			"CURSOR_UP",			"\x1b[1;5A",		event_cursor_up },
		{ CURSOR_DOWN_EVID,			"CURSOR_DOWN",			"\x1b[1;5B",		event_cursor_down },
		{ CURSOR_DOWN_EVID,			"CURSOR_DOWN",			"\x1b\x5b\x36\x7e",	event_cursor_down },
		{ CURSOR_HOME_EVID,			"CURSOR_HOME",			"\x1b[H",			event_cursor_home },
		{ CURSOR_END_EVID,			"CURSOR_END",			"\x1b[F",			event_cursor_end },
		{ CURSOR_WORD_RIGHT_EVID,	"CURSOR_WORD_RIGHT",	"\x1b[1;5C",		event_cursor_word_right },
		{ CURSOR_WORD_LEFT_EVID,	"CURSOR_WORD_LEFT",		"\x1b[1;5D",		event_cursor_word_left },
		{ HISTORY_UP_EVID,			"HISTORY_UP",			"\x1b[A",			event_history_up },
		{ HISTORY_DOWN_EVID,		"HISTORY_DOWN",			"\x1b[B",			event_history_down },
		{ COPY_EVID,				"COPY",					"\x2",				event_copy },
		{ CUT_EVID,					"CUT",					"\xb",				event_cut },
		{ PASTE_EVID,				"PASTE",				"\x10",				event_paste },
		{ CANCEL_EVID,				"CANCEL",				"\x3",				event_cancel },
		{ EXIT_EVID,				"EXIT",					"\x4",				event_exit },
		{ DELETE_EVID,				"DELETE",				"\x7f",				event_delete }
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
