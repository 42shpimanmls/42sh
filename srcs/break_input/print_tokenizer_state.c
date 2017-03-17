#include "tokenizer.h"
#include <libft.h>
#include "utils.h"
#include "quoting.h"

// DANGER
#include <stdio.h>

void			print_tokenizer_state(t_tokenizer_state *state)
{
#ifdef TOKENIZER_DEBUG
	ft_putstr("'");
	print_non_ascii_char(*state->current_char);
	printf("'@%ld%s last_bsl@%ld sim_quo_end@%ld  dub_quo_end@%ld\n", state->current_char - state->input, is_quoted(state) ? " QUOTED" : ""
		, state->last_backslash ? state->last_backslash - state->input : -1
		, state->simple_quote_end ? state->simple_quote_end - state->input : -1
		, state->double_quote_end ? state->double_quote_end - state->input : -1);
#else
	(void)state;
#endif
}
