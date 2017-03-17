#ifndef SYNTAX_TREE_H
# define SYNTAX_TREE_H

#include "shell_env.h"
#include "uint.h"

typedef struct		s_redirection
{
	struct s_redirection	*next;
	t_uint					n;
	t_token_id				redir_op;
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
	t_token_id				separation_type;
}					t_and_or_list;

typedef struct		s_command_list
{
	struct s_command_list	*next;
	t_and_or_list			*and_or_list;
}					t_command_list;

#endif
