#include "abstract_list.h"
#include "utils.h"

#include "break_input/tokenizer_state.h"

static void		add_quote_to_token(t_token *token)
{
	char *tmp;

	while (token->next)
		token = token->next;
	tmp = ft_strjoin(token->str, "\"");
	ft_strdel(&token->str);
	token->str = ft_strdup(tmp);
	ft_strdel(&tmp);
	set_error(NO_ERROR);
	get_shell_env()->last_unmatched = NO_ERROR;
}

static void		add_quote_token(t_tokenizer_state const state, t_token *result)
{
	t_token		*token;
	char		*str;
	char		*tmp;

	tmp = ft_strdup(state.current_char);
	str = ft_strtrim(tmp);
	ft_strdel(&tmp);
	token = construct_token(str, *state.current_char);
	list_push_back((t_abstract_list**)&result
				, (t_abstract_list*)token);
	ft_strdel(&str);
	set_error(NO_ERROR);
}

void			add_token_quote(t_tokenizer_state state, t_token *result)
{
	if (*state.current_char == '"' && *(state.current_char - 1) == ' ')
		add_quote_token(state, result);
	else if (*state.current_char == '"')
		add_quote_to_token(result);
}
