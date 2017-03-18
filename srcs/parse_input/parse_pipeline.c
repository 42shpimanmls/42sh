#include "parse_syntax_tree.h"
#include "syntax_tree.h"
#include "utils.h"
#include "abstract_list.h"
#include <libft.h>

t_simple_command	*parse_pipeline(t_token const *tokens)
{
	t_simple_command	*result;
	t_simple_command	**it;
	t_token				**splited;
	t_token				*trimed;
	size_t				splited_len;
	size_t				u;

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
			ft_putendl_fd(
				"42sh: syntax error near unexpected token '|'", 2);
			exit(1);
		}
		(*it) = parse_simple_command(trimed);
		delete_all_tokens(&trimed);
		it = &(*it)->next;
		u++;
	}
	delete_tokens_array(splited, splited_len);
	return (result);
}
