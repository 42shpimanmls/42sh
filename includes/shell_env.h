#ifndef SHELL_ENV_H
# define SHELL_ENV_H

# include <stdlib.h>
# include <libft.h>
# include <stdbool.h>
# include "break_input/token.h"
# include "parse_input/syntax_tree.h"
# include "variable.h"
# include "errors.h"

/* proposition

typedef struct 			s_history
{
	size_t			size;
	t_history_list	*last_elem
	t_history_list	*history_list;
}

OR liste circulaire

*/

# define SHNAME "42sh"
# define PROMPT "SUprompt> "

typedef struct			s_history
{
	struct s_history	*next;
	char				*line;
	bool				appended;
	struct s_history	*prev;
}						t_history;

typedef struct			s_shell_env
{
	t_variable			*variables;
	t_history			*history;
	bool				should_run;
	bool				should_keep_reading;
	char				*command_string;
	char				*input_string;
	t_token				*tokens;
	t_command_list		*syntax_tree;
	t_error_id			last_unmatched;
}						t_shell_env;

t_shell_env				*get_shell_env(void);

#endif
