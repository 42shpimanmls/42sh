#ifndef BUILTINS_H
# define BUILTINS_H

#include "variable.h"
# include "../../parse_input/syntax_tree.h"

# define STATUS_SUCCESS 0
# define STATUS_FAILURE -1
# define BUILTIN_RET int
# define BUILTIN_ARGS int argc, char **argv

typedef BUILTIN_RET	(*t_builtin)(BUILTIN_ARGS);

BUILTIN_RET 		builtin_cd(BUILTIN_ARGS);
BUILTIN_RET 		builtin_setenv(BUILTIN_ARGS);
BUILTIN_RET 		builtin_unsetenv(BUILTIN_ARGS);
BUILTIN_RET 		builtin_set(BUILTIN_ARGS);
BUILTIN_RET 		builtin_export(BUILTIN_ARGS);
BUILTIN_RET 		builtin_unset(BUILTIN_ARGS);
BUILTIN_RET 		builtin_exit(BUILTIN_ARGS);
BUILTIN_RET			builtin_history(BUILTIN_ARGS);

/*
**
**	SUB BUILTIN
**	
*/

/*
** setenv, unsetenv
*/
int	 		setenv_as(t_variable **env, char *name, char *value, bool exported);
int 		unsetenv_as(t_variable **env, char *name);
/*
** echo
*/

int			builtin_echo(int argc, char **argv);
void			display_echo(int argc, char **argv, char *opt, int i);
bool		escape_char(char *str);
bool		escape(int c);
int			octal(char *c);

/*
** env.c
*/
int			builtin_env(BUILTIN_ARGS, t_simple_command *cmd);
void			run_env(BUILTIN_ARGS, t_simple_command *cmd);

#endif
