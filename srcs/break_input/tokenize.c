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

void			reset_tokenizer_input(t_tokenizer_state *state, char const *input)
{
	free(state->input);
	ft_bzero(state, sizeof(t_tokenizer_state));
	state->input = ft_strdup(input);
}

#include <stdio.h>

t_token			*tokenize(char const *input)
{
	t_token						*result;
	static t_tokenizer_state	state = {
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
	};
	char						*str;

	result = NULL;
	if (input != NULL)
	{
		str = state.input;
		state.input = ft_strjoin(state.input, input);
		free(str);
		if (state.input == NULL)
			return (NULL);
		state.current_char = state.input;
		set_error(NO_ERROR);
		while (*state.current_char != '\0')
		{
			apply_rules(&state);
			if (get_error() != NO_ERROR)
			{
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
		reset_tokenizer_input(&state, "");
	}
	return (result);
}
