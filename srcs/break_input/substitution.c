#include <stdbool.h>
#include <libft.h>
#include "errors.h"
#include "shell_env.h"

bool		is_substitution_start(char const *s)
{
	if (s && *s == '`')
		return (true);
	return (false);
}

char const	*find_substitution_end(char const *str)
{
	set_error(NO_ERROR);
	while (*str)
	{
		if (*str == '`')
			return (str);
		str++;
	}
	set_error(UNMATCHED_BACKQUOTE);
	get_shell_env()->last_unmatched = UNMATCHED_BACKQUOTE;
	return (str);
}
