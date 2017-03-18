#include "parse_syntax_tree.h"
#include "abstract_list.h"
#include "utils.h"
#include <libft.h>

static char			**parse_argv(t_token const *tokens)
{
	char	**result;
	size_t	len;
	char	**it;

	len = list_count((t_abstract_list*)tokens);
	result = memalloc_or_die(sizeof(char*) * (len + 1));
	it = result;
	while (tokens != NULL)
	{
		*it = ft_strdup(tokens->str);
		it++;
		tokens = tokens->next;
	}
	*it = NULL;
	return (result);
}

t_simple_command	*parse_simple_command(t_token const *tokens)
{
	t_simple_command *result;

	if (tokens == NULL)
		return (NULL);
	result = memalloc_or_die(sizeof(t_simple_command));
	result->argv = parse_argv(tokens);
	return (result);
}
