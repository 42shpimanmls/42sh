#ifndef BUILTINS_H
# define BUILTINS_H

/*# include "builtin_args.h"*/

# define STATUS_SUCCESS 0
# define BUILTIN_RET int
# define BUILTIN_ARGS int argc, char **argv

typedef BUILTIN_RET	(*t_builtin)(BUILTIN_ARGS);

BUILTIN_RET 		builtin_cd(BUILTIN_ARGS);
BUILTIN_RET 		builtin_setenv(BUILTIN_ARGS);
BUILTIN_RET 		builtin_unsetenv(BUILTIN_ARGS);
BUILTIN_RET 		builtin_exit(BUILTIN_ARGS);

#endif
