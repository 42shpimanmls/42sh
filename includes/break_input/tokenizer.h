#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "tokenizer_state.h"

t_token		*tokenize(char const *input);

void		apply_rules(t_tokenizer_state *state);
void		delimit_token(t_tokenizer_state *state);
void		print_tokenizer_state(t_tokenizer_state *state);

#endif
