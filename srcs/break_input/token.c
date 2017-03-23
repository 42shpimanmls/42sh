#include "utils.h"
#include "token.h"
#include <libft.h>
#include "break_input/lexer.h"
#include "abstract_list.h"

t_token	*construct_token(char const *str, char delim)
{
	t_token	*token;

	token = memalloc_or_die(sizeof(t_token));
	token->type = get_token_def(TOKEN_TOKID);
	token->str = ft_strdup(str);
	lex_me(token, delim);
	return (token);
}

t_token	*tokens_dup_until(t_token const *tokens, t_token const *stop)
{
	t_token	*result;
	t_token	**it;

	result = NULL;
	it = &result;
	while (tokens != NULL && tokens != stop)
	{
		*it = memalloc_or_die(sizeof(t_token));
		(*it)->str = ft_strdup(tokens->str);
		(*it)->type = tokens->type;
		it = &(*it)->next;
		tokens = tokens->next;
	}
	*it = NULL;
	return (result);
}

size_t		count_token_type(t_token const *tokens, t_token_id type)
{
	if (tokens == NULL)
		return (0);
	else if (tokens->type->id == type)
		return (count_token_type(tokens->next, type) + 1);
	else
		return (count_token_type(tokens->next, type));
}

size_t		count_token_types(t_token const *tokens
	, t_token_id const *types, size_t nbr_types)
{
	if (tokens == NULL)
		return (0);
	else if (token_is_one_of_types(tokens, types, nbr_types))
		return (count_token_types(tokens->next, types, nbr_types) + 1);
	else
		return (count_token_types(tokens->next, types, nbr_types));
}

bool		token_is_one_of_types(t_token const *token, t_token_id const *types
	, size_t nbr_types)
{
	while (nbr_types > 0)
	{
		nbr_types--;
		if (token->type->id == types[nbr_types])
			return (true);
	}
	return (false);
}

void		delete_tokens_array(t_token **tokens_array, size_t len)
{
	if (tokens_array == NULL)
		return ;
	while (len > 0)
	{
		len--;
		delete_all_tokens(tokens_array + len);
	}
	free (tokens_array);
}

t_token			*copy_token(t_token const *src)
{
	t_token	*dst;

	dst = memalloc_or_die(sizeof(t_token));
	dst->str = ft_strdup(src->str);
	dst->type = src->type;
	return (dst);
}

t_token			*copy_all_tokens(t_token const *src)
{
	t_token	*dst;
	t_token	**next_addr;

	dst = NULL;
	next_addr = &dst;
	while (src)
	{
		*next_addr = copy_token(src);
		src = src->next;
		next_addr = &((*next_addr)->next);
	}
	return (dst);
}
