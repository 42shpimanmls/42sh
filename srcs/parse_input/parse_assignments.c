#include "parse_syntax_tree.h"
#include "abstract_list.h"
#include "utils.h"
#include <libft.h>
#include "errors.h"
#include "variable.h"

static bool				is_xbd_name_char(char c, size_t u)
{
	if (u == 0 && ft_isdigit(c))
		return (false);
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

static char const		*find_assignment_equal(char const *str)
{
	char	c;
	size_t	u;

	u = 0;
	while ((c = str[u]) != '\0')
	{
		if (!is_xbd_name_char(c, u))
		{
			if (c == '=' && u != 0)
				return (str + u);
			else
				return (NULL);
		}
		u++;
	}
	return (NULL);
}

static t_variable		*create_assignment(t_token const *token)
{
	char const	*equal_pos;
	char		*name;
	char		*value;

	equal_pos = find_assignment_equal(token->str);
	if (equal_pos == NULL)
		return (NULL);
	name = strdup_until(token->str, equal_pos);
	value = ft_strdup(equal_pos + 1);
	return (create_variable(name, value, false));
}

t_variable				*parse_assignments(t_token const *tokens\
											, t_token **remains)
{
	t_variable	*result;
	t_variable	**next_addr;

	*remains = NULL;
	result = NULL;
	next_addr = &result;
	while (tokens != NULL)
	{
		*next_addr = create_assignment(tokens);
		if (*next_addr == NULL)
		{
			// if a word is not an assignment then we're done parsing assignments
			*remains = copy_all_tokens(tokens);
			break ;
		}
		next_addr = &(*next_addr)->next;
		tokens = tokens->next;
	}
	return (result);
}
