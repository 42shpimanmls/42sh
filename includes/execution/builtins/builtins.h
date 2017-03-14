#ifndef BUILTINS
# define BUILTINS

/*# include "builtin_args.h"*/

# define BUILTIN_RET void
# define BUILTIN_ARGS /*t_builtin_args *smth*/

typedef BUILTIN_RET	(*t_builtin)(BUILTIN_ARGS);

BUILTIN_RET 		builtin_cd(BUILTIN_ARGS);

#endif
