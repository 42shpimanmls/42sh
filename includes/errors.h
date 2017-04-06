#ifndef ERRORS_H
# define ERRORS_H

#include "execution/builtins/builtin_def.h"

typedef enum				e_error_id
{
	NO_ERROR = 0,
	TOO_MANY_ARGS,
	NEED_ARG,
	NEED_NUM,
	OUT_OF_RANGE,
	INVALID_OPTION,
	EV_NOT_FOUND,
	BAD_WD_SPEC,
	PERM_DENIED,
	NO_SUCH_FILE,
	UNMATCHED_SINGLE_QUOTE,
	UNMATCHED_DOUBLE_QUOTE,
	UNMATCHED_BACKQUOTE,
	UNEXPECTED_SEMI,
	UNEXPECTED_IF,
	UNEXPECTED_PIPE,
	NO_SUCH_BUILTIN,
	CHILD_FAILURE
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

#define TOTAL_ERROR_COUNT 18

t_error const 		*get_error_defs(void);
void				print_error_msg(t_error_id id);
void				print_usage_msg(t_builtin_id id);
void				print_name_and_error(t_error_id id);

t_error_id			get_error(void);
void				set_error(t_error_id error);

void				error_builtin(char *builtin, char *error, t_error_id id);

void				print_system_error_list(int signum);

#endif
