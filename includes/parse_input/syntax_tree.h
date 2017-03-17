#ifndef SYNTAX_TREE_H
# define SYNTAX_TREE_H

# include "shell_env.h"
# include "uint.h"

typedef enum	e_ao_type
{
	AO_OR = OR_IF_TOKID,
	AO_AND = AND_IF_TOKID,
	AO_END = TOKEN_TOKID
}				t_ao_type;

typedef enum	e_redir_type
{
	REDIR_OUTPUT = GREAT_TOKID,
	REDIR_INPUT = LESS_TOKID,
	APPEND_OUTPUT = DGREAT_TOKID
}				t_redir_type;

typedef struct		s_redirection
{
	struct s_redirection	*next;
	t_uint					n;
	t_redir_type			type;
	char const				*word;
}					t_redirection;

typedef struct		s_simple_command
{
	struct s_simple_command	*next;
	t_variable				*assignments;
	t_redirection			*redirections;
	char *const				*argv;
}					t_simple_command;

typedef struct		s_and_or_list
{
	struct s_and_or_list	*next;
	t_simple_command		*pipeline;
	t_ao_type				separation_type;
}					t_and_or_list;

typedef struct		s_command_list
{
	struct s_command_list	*next;
	t_and_or_list			*and_or_list;
}					t_command_list;

#endif
