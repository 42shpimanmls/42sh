#include "tokenizer.h"
#include "utils.h"
#include <libft.h>
#include "abstract_list.h"

void			delimit_token(t_tokenizer_state *state)
{
	char		*str;
	t_token		*token;
	char const	*start;

	if (state->op_start)
		start = state->op_start;
	else
		start = state->word_start;
	if (!start)
		return ;
	str = strdup_until(start, state->current_char);
	if (*str != '\0')
	{
		token = construct_token(str, *state->current_char);
#ifdef TOKENIZER_DEBUG
		ft_putstr("DELIMITED: ");
		print_token(token);
#endif
		list_push_back((t_abstract_list**)&state->result
			, (t_abstract_list*)token);
	}
	free(str);
	state->op_start = NULL;
	state->word_start = NULL;
}
