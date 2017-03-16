#ifndef TOKENIZER_STATE
# define TOKENIZER_STATE

# include "token.h"

typedef struct		s_tokenizer_state
{
	char const	*input;
	char const	*current_char;
	char const	*word_start;
	char const	*op_start;
	t_token		*result;
	char const	*last_backslash;
	char const	*simple_quote_end;
	char const	*double_quote_end;
}					t_tokenizer_state;

#endif
