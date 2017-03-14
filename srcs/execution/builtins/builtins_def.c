#include "builtin_def.h"
#include <stdlib.h>
#include "uint.h"
#include <libft.h>

t_builtin_def const			*get_builtin_defs(void)
{
	static t_builtin_def const defs[BUILTIN_DEF_COUNT] =
	{
	//	ID							NAME					HANDLER FUNCTION
		{ CD_BUID,					"cd",					NULL },
		{ ECHO_BUID,				"echo",					NULL },
		{ EXIT_BUID,				"exit",					NULL },
		{ SETENV_BUID, 				"setenv",				NULL },
		{ UNSETENV_BUID, 			"unsetenv",				NULL },
		{ UNSET_BUID, 				"unset",				NULL },
		{ EXPORT_BUID,				"export",				NULL },
		{ HISTORY_BUID,				"history",				NULL },
		{ ENV_BUID,					"env",					NULL }
	};
	return (defs);
}

t_builtin_def const			*get_matching_builtin(char const *str)
{
	t_uint						u;
	t_builtin_def const	*defs;

	defs = get_builtin_defs();
	u = 0;
	while (u < BUILTIN_DEF_COUNT)
	{
		if (defs[u].name != NULL && ft_strequ(defs[u].name, str))
			return (defs + u);
		u++;
	}
	return (NULL);
}
