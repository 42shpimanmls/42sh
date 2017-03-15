#include "utils.h"
#include "token.h"
#include <libft.h>

t_token	*construct_token(t_token_id id, char const *str, char delim)
{
	t_token	*token;

	token = memalloc_or_die(sizeof(t_token));
	token->type = get_token_def(id);
	token->str = ft_strdup(str);
	token->delimiter = delim;
	return (token);
}
