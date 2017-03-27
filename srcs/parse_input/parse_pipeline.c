#include "parse_syntax_tree.h"
#include "syntax_tree.h"
#include "utils.h"
#include "abstract_list.h"
#include <libft.h>
#include "errors.h"
#include "shell_env.h"

t_simple_command	*parse_pipeline(t_token const *tokens)
{
	t_simple_command	*result;
	t_simple_command	**it;
	t_token				**splited;
	t_token				*trimed;
	size_t				splited_len;
	size_t				u;

	set_error(NO_ERROR);
	if (tokens == NULL)
		return (NULL);
	splited = split_tokens_at(tokens, OR_TOKID, &splited_len);
	u = 0;
	result = NULL;
	it = &result;
	while (u < splited_len)
	{
		trimed = trim_newlines(splited[u]);
		if (trimed == NULL)
		{
			set_error(UNEXPECTED_PIPE);
			if (u == splited_len - 1)
				get_shell_env()->last_unmatched = UNEXPECTED_PIPE;
			result = NULL; //delete_command_list(&result);
			break ;
		}
		(*it) = parse_simple_command(trimed);
		delete_all_tokens(&trimed);
		if (get_error() != NO_ERROR)
		{
			result = NULL; //delete_command_list(&result);
			break ;
		}
		it = &(*it)->next;
		u++;
	}
	delete_tokens_array(splited, splited_len);
	return (result);
}
