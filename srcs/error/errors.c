#include "errors.h"
#include "libft.h"
#include "uint.h"
#include <stdlib.h>

t_error const			*get_error_defs(void)
{
	static t_error const errors[TOTAL_ERROR_COUNT] =
	{
		// ID 					// MSG
		{ TOO_MANY_ARGS,		"too many arguments" },
		{ NEED_ARG, 			"option requires an argument" },
		{ NEED_NUM,				"numeric argument required" },
		{ OUT_OF_RANGE,			"history position out of range" },
		{ INVALID_OPTION,		"invalid option" },
		{ EV_NOT_FOUND,			"event not found"},
		{ BAD_WD_SPEC,			"bad word specifier"},
		{ PERM_DENIED,			"permission denied" },
		{ NO_SUCH_FILE,			"no such file or directory" },
		{ UNMATCHED_SINGLE_QUOTE,	"syntax error: unmatched '"},
		{ UNMATCHED_DOUBLE_QUOTE,	"syntax error: unmatched \""},
		{ UNMATCHED_BACKQUOTE,		"syntax error: unmatched `"},
	};
	return (errors);
}
