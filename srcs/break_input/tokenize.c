#include "token.h"
#include <libft.h>
#include "tokenizer.h"
#include "errors.h"

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
