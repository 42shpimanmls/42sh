#include "parse_syntax_tree.h"
#include "syntax_tree.h"
#include "utils.h"
#include "abstract_list.h"
#include <libft.h>
#include "errors.h"

static bool		last_is_semi(t_token const *tokens)
{
	t_token const *last;

	if (tokens == NULL)
		return (false);
	last = (t_token const *)list_get_last_const(
		(t_abstract_list const *)tokens);
	if (last->type->id == SEMI_TOKID)
		return (true);
	else
		return (false);
}

t_command_list	*parse_command_list(t_token const *tokens)
{
	t_command_list	*result;
	t_command_list	**it;
	t_token			**splited;
	size_t			splited_len;
	size_t			u;
	t_token			*trimed;

	set_error(NO_ERROR);
	if (tokens == NULL)
		return (NULL);
	trimed = trim_newlines(tokens);
	splited = split_tokens_at(trimed, SEMI_TOKID, &splited_len);
	result = NULL;
	if (splited_len > 1 || splited[0] != NULL)
	{
		if (last_is_semi(trimed))
			splited_len--;
		u = 0;
		it = &result;
		while (u < splited_len)
		{
			if (splited[u] == NULL)
			{
				set_error(UNEXPECTED_SEMI);
				result = NULL; //delete_command_list(&result);
				break ;
			}
			(*it) = memalloc_or_die(sizeof(t_command_list));
			(*it)->and_or_list = parse_and_or_list(splited[u]);
			if (get_error() != NO_ERROR)
			{
				result = NULL; //delete_command_list(&result);
				break ;
			}
			it = &(*it)->next;
			u++;
		}
	}
	delete_all_tokens(&trimed);
	delete_tokens_array(splited, splited_len);
	return (result);
}
