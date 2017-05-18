#include "token.h"
#include <stdlib.h>
#include "utils.h"
#include <libft.h>
#include "abstract_list.h"
#include "tokenizer.h"
#include "utils.h"
#include "quoting.h"
#include "substitution.h"
#include "errors.h"

static bool		is_operator_part(t_tokenizer_state *state)
{
	char		*str;
	bool		result;
	char const	*start;

	if (state->op_start != NULL)
		start = state->op_start;
	else
		start = state->current_char;
	str = strdup_until(start, state->current_char + 1);
	if (get_matching_operator(str) != NULL)
		result = true;
	else
		result = false;
	free(str);
	return (result);
}

void			apply_rules(t_tokenizer_state *state)
{
	char c;

	c = *state->current_char;
	print_tokenizer_state(state);
	// rule 2
	if (state->op_start != NULL && !is_quoted(state)
		&& is_operator_part(state))
	{
		state->current_char++;
		return ;
	}
	// rule 3
	if (state->op_start != NULL && !is_operator_part(state))
	{
		delimit_token(state);
		return ;
	}
	// rule 4
	if (is_quote(c) && !is_quoted(state))
	{
		apply_quoting(state);
		return ;
	}
	// rule 5 (incomplete !! recursion not handled) // not quoted if double quotes?
	if (!is_quoted(state) && is_substitution_start(state->current_char))
	{
		// Weird, not referenced but necessary (or illogism)
		if (state->word_start == NULL)
			state->word_start = state->current_char;
		state->current_char =
			find_substitution_end(state->current_char + 1) + 1;
		return ;
	}
	// rule 6
	if (!is_quoted(state) && is_operator_part(state))
	{
		delimit_token(state);
		state->op_start = state->current_char;
		state->current_char++;
		return ;
	}
	// rule 7
	if (!is_quoted(state) && is_posix_blank(c))
	{
		delimit_token(state);
		state->current_char++;
		return ;
	}
	// rule 8
	if (state->word_start != NULL)
	{
		state->current_char++;
		return ;
	}
	// rule 9
	if (c == '#')
	{
		while (*(state->current_char) != '\0'
			&& *(state->current_char) != '\n')
			state->current_char++;
		return ;
	}
	// rule 10
	state->word_start = state->current_char;
	state->current_char++;
}
