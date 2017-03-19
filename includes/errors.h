#ifndef ERRORS_H
# define ERRORS_H

#include "execution/builtins/builtin_def.h"

typedef enum				e_error_id
{
	TOO_MANY_ARGS = 0,
	NEED_ARG,
	NEED_NUM,
	OUT_OF_RANGE,
	INVALID_OPTION,
	EV_NOT_FOUND,
	BAD_WD_SPEC,
	PERM_DENIED,
	NO_SUCH_FILE
}							t_error_id;

typedef struct 			s_error
{
	t_error_id			id;
	char const	*const 	msg;
}						t_error;

typedef struct s_builtin_usage
{
	t_builtin_id id;
	char	*msg;
}				t_builtin_usage;

#define TOTAL_ERROR_COUNT 9

t_error const 		*get_error_defs(void);
void				print_error_msg(t_error_id id);
void				print_usage_msg(t_builtin_id id);

void				error_builtin(char *builtin, char *error, t_error_id id);

#endif
