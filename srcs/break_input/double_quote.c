#include "quoting.h"
#include "substitution.h"
#include <libft.h>
#include "errors.h"

char const	*find_double_quote_end(t_tokenizer_state *state)
{
	char const *it;
	char nc;

	it = state->current_char + 1;
	while (*it != '\0')
	{
		nc = *(it + 1);
		if (*it == '`')
			it = find_substitution_end(it + 1);
		if (*it == '\\' && (nc == '`' || nc == '"' || nc == '\\' || nc == '\n'))
			it++;
		else if (*it == '"')
			return (it);
		it++;
	}
	ft_putendl_fd("42sh: syntax error: missing double quote end\n", 2);
	set_error(UNMATCHED_DOUBLE_QUOTE);
	return (NULL);
}

bool		is_double_quoted(t_tokenizer_state *state)
{
	char c;
	char nc;

	if (state->double_quote_end >= state->current_char)
	{
		c = *state->current_char;
		if (c == '`')
			return (false);
		else if (c == '\\')
		{
			nc = *(state->current_char + 1);
			if (nc == '`' || nc == '"' || nc == '\\' || nc == '\n')
				return (false);
		}
		return (true);
	}
	else
		return (false);
}
