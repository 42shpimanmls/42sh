#include "token.h"
#include <stdlib.h>
#include "utils.h"
#include <libft.h>
#include "abstract_list.h"
#include "tokenizer.h"

t_token			*tokenize(char const *input)
{
	t_tokenizer_state state;

	ft_bzero(&state, sizeof(t_tokenizer_state));
	state.input = input;
	if (state.input != NULL)
	{
		state.current_char = state.input;
		while (*state.current_char != '\0')
			apply_rules(&state);
		// rule 1
		print_tokenizer_state(&state);
		delimit_token(&state);
		ft_putstr("rule 1 aka I'M DONE MOTHERF***ERZ\n");
	}
	return (state.result);
}
