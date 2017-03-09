#ifndef TOKEN_H
# define TOKEN_H

# include "token_def.h"

typedef struct	s_token
{
	char const			*data;
	t_token_def const	*info;
	char				delimiter;
}				t_token;

#endif
