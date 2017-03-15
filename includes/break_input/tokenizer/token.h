#ifndef TOKEN_H
# define TOKEN_H

# include "token_def.h"

typedef struct	s_token
{
	struct s_token		*next;
	t_token_def const	*type;
	char				*str;
	//struct s_token		*prev; ?
}				t_token;

t_token	*construct_token(char const *str, char delim);

void	print_token(t_token const *token);
void	print_tokens(t_token const *tokens);

#endif
