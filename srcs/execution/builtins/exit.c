#include "builtins.h"
#include <stdlib.h>

BUILTIN_RET 		builtin_exit(BUILTIN_ARGS)
{
	(void)argc;
	(void)argv;
	exit(EXIT_SUCCESS);
}
