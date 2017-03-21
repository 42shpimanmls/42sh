#include "token.h"
#include <stdlib.h>
#include "utils.h"
#include <libft.h>
#include "abstract_list.h"
#include "tokenizer.h"
#include "errors.h"

bool			unmatched_error()
{
	t_error_id	error;

	error = get_error();
	if (error == UNMATCHED_SINGLE_QUOTE
		|| error == UNMATCHED_DOUBLE_QUOTE
		|| error == UNMATCHED_BACKQUOTE)
		return (true);
	return (false);
}

t_token			*tokenize(char const *input)
{
	t_token						*result;
	t_tokenizer_state			state;

	set_error(NO_ERROR);
	result = NULL;
	if (input != NULL)
	{
		ft_bzero(&state, sizeof(t_tokenizer_state));
		state.input = ft_strdup(input);
		state.current_char = state.input;
		while (*state.current_char != '\0')
		{
			apply_rules(&state);
			if (get_error() != NO_ERROR)
			{
				free(state.input);
				delete_all_tokens(&state.result);
				return (NULL);
			}
		}
		// rule 1
#ifdef TOKENIZER_DEBUG
		print_tokenizer_state(&state);
		ft_putstr("rule 1 aka I'M DONE MOTHERF***ERZ\n");
#endif
		delimit_token(&state);
		result = state.result;
		free(state.input);
	}
	return (result);
}
