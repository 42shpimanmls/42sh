#include <stdlib.h>
#include "uint.h"
#include "token_def.h"

// REMPLACER LE STRLEN ET STRNCMP
#include <string.h>

t_token_def const			*get_matching_operator(char const *str)
{
	t_uint				u;
	t_token_def const	*defs;

	defs = get_token_defs();
	u = 0;
	while (u < TOKEN_DEF_COUNT)
	{
		if (defs[u].str != NULL && strncmp(defs[u].str, str, strlen(str)) == 0)
			return (defs + u);
		u += 1;
	}
	return (NULL);
}
