#include "break_input/tokenizer/token.h"
#include <stdlib.h>
#include <libft.h>

static bool	lex_operator(t_token *token)
{
	t_token_def const	*match;

	match = get_matching_operator(token->str);
	if (match != NULL)
	{
		token->type = match;
		return (true);
	}
	return (false);
}

static bool	str_is_digits(char const *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str += 1;
	}
	return (true);
}

static bool	is_io_number(char c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}

static bool	lex_io_number(t_token *token, char delim)
{
	if (str_is_digits(token->str) && is_io_number(delim))
	{
		token->type = get_token_def(IO_NUMBER_TOKID);
		return (true);
	}
	return (false);
}

void		lex_me(t_token *token, char delim)
{
	if (!lex_operator(token))
		lex_io_number(token, delim);
}
