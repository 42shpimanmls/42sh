#ifndef BUILTINS_H
# define BUILTINS_H

#include "variable.h"
#include "opt.h"
/*# include "builtin_args.h"*/

# define STATUS_SUCCESS 0
# define BUILTIN_RET int
# define BUILTIN_ARGS int argc, char **argv

typedef BUILTIN_RET	(*t_builtin)(BUILTIN_ARGS);

BUILTIN_RET 		builtin_cd(BUILTIN_ARGS);
BUILTIN_RET 		builtin_setenv(BUILTIN_ARGS);
BUILTIN_RET 		builtin_unsetenv(BUILTIN_ARGS);
BUILTIN_RET 		builtin_exit(BUILTIN_ARGS);
BUILTIN_RET			builtin_history(BUILTIN_ARGS);

/*
**
**	SUB BUILTIN
**	
*/

/*
** options
*/
int					retrieve_options(int argc, char **argv, t_opt *o);

/*
** setenv, unsetenv
*/
void 			setenv_as(t_variable **env, char *name, char *value);
void 			unsetenv_as(t_variable **env, char *name);
/*
** echo
*/

int					builtin_echo(int argc, char **argv);
void				escape_char(char *str);
void				escape(int c);
int					octal(char *c);
int					convert_base(int nbr, int base_from, int base_to);

#endif
