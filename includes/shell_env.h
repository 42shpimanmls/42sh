#ifndef SHELL_ENV_H
# define SHELL_ENV_H

# include <stdlib.h>
# include <libft.h>
# include <stdbool.h>
# include "break_input/token.h"
# include "parse_input/syntax_tree.h"
# include "variable.h"
# include "errors.h"
# include "history/history_def.h"

# define SHNAME "42sh"

typedef struct			s_shell_env
{
	t_variable			*variables;
	t_sh_history		history;
	t_file_position		*history_files;
	bool				should_run;
	bool				should_keep_reading;
	char				*command_string;
	char				*input_string;
	t_token				*tokens;
	t_command_list		*syntax_tree;
	t_error_id			last_unmatched;
	char const			*path_to_42sh;
}						t_shell_env;

t_shell_env				*get_shell_env(void);

#endif
