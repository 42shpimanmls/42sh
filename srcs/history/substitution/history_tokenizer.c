#include "shell_env.h"

#include "abstract_list.h"
#include "utils.h"
#include "uint.h"

#include "break_input/tokenizer.h"
#include "history_substitutions.h"

/*
**	slightly modified tokenizer to handle 'bli bla "!!' case
**	(bang isn't quoted with double quotes, so substitution IS made)
**	add bool to original tokenizer?
*/

static bool		terminate_tokenizer(t_tokenizer_state state)
{
	if (get_error() == UNMATCHED_DOUBLE_QUOTE)
		return (false);
	free(state.input);
	delete_all_tokens(&state.result);
	return (true);
}

static void		end_tokenizer(t_tokenizer_state state, t_token **result)
{
	delimit_token(&state);
	*result = state.result;
	if (get_error() == UNMATCHED_DOUBLE_QUOTE)
		add_token_quote(state, *result);
	free(state.input);
}

t_token			*tokenize_for_substitution(char const *input)
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
				if (terminate_tokenizer(state))
					return (NULL);
				break ;
			}
		}
		end_tokenizer(state, &result);
	}
	return (result);
}
