#ifndef PARSE_SYNTAX_TREE_H
# define PARSE_SYNTAX_TREE_H

# include "syntax_tree.h"

t_command_list		*parse_command_list(t_token const *tokens);
t_and_or_list		*parse_and_or_list(t_token const *tokens);
t_simple_command	*parse_pipeline(t_token const *tokens);
t_simple_command	*parse_simple_command(t_token const *tokens);
t_variable			*parse_assignments(t_token const *tokens\
										, t_token **remains);
t_redirection		*parse_redirections(t_token const *tokens\
										, t_token **remains);

#endif
