#include "utils.h"
#include "token.h"
#include <libft.h>
#include "break_input/lexer.h"

t_token	*construct_token(char const *str, char delim)
{
	t_token	*token;

	token = memalloc_or_die(sizeof(t_token));
	token->type = get_token_def(TOKEN_TOKID);
	token->str = ft_strdup(str);
	token->delimiter = delim;
	lex_me(token);
	return (token);
}
