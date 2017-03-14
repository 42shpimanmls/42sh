#ifndef TOKEN_H
# define TOKEN_H

# include "token_def.h"

typedef struct	s_token
{
	t_token_def const	*type;
	char				*str;
	char				delimiter;
	struct s_token		*next;
	//struct s_token		*prev; ?
}				t_token;

#endif
