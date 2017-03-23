#include "parse_syntax_tree.h"
#include "abstract_list.h"
#include "utils.h"
#include <libft.h>
#include "errors.h"
#include "variable.h"

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

bool					is_xbd_name_char(char c, size_t u)
{
	if (u == 0 && ft_isdigit(c))
		return (false);
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

#include <stdio.h>

char const				*find_assignment_equal(char const *str)
{
	char	c;
	size_t	u;

	u = 0;
	while ((c = str[u]) != '\0')
	{
		if (!is_xbd_name_char(c, u))
		{
			if (c == '=')
				return (str + u);
			else
				return (NULL);
		}
		u++;
	}
	return (NULL);
}

t_variable				*create_assignment(t_token const *token)
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

t_variable				*parse_assignments(t_token const *tokens, t_token **remains)
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

t_redirection			*create_redirection(t_token const *tokens, t_token const **end)
{
	t_redirection		*result;

	if (tokens == NULL)
		return (NULL);
	result = memalloc_or_die(sizeof(t_redirection));
	if (tokens->type->id == IO_NUMBER_TOKID)
	{
		result->n = ft_atoi(tokens->str);
		tokens = tokens->next;
	}
	else
		result->n = -1;
	if (tokens == NULL || (tokens->type->id != (t_token_id)REDIR_OUTPUT
					&& tokens->type->id != (t_token_id)REDIR_INPUT
					&& tokens->type->id != (t_token_id)APPEND_OUTPUT))
		return (NULL);
	result->type = (t_redir_type)tokens->type->id;
	tokens = tokens->next;
	if (tokens == NULL || tokens->type->id != TOKEN_TOKID)
		return (NULL);
	result->word = ft_strdup(tokens->str);
	*end = tokens->next;
	return (result);
}

t_redirection			*parse_redirections(t_token const *tokens, t_token **remains)
{
	t_redirection	*result;
	t_redirection	**next_addr;
	t_token			**next_remain;

	*remains = NULL;
	result = NULL;
	next_addr = &result;
	next_remain = remains;
	while (tokens != NULL)
	{
		*next_addr = create_redirection(tokens, &tokens);
		if (*next_addr == NULL)
		{
			// if the word is not part of redirection, copy it in remains
			*next_remain = copy_token(tokens);
			next_remain = &(*next_remain)->next;
			tokens = tokens->next;
		}
		else
			next_addr = &(*next_addr)->next;
	}
	return (result);
}

t_simple_command	*parse_simple_command(t_token const *tokens)
{
	t_simple_command	*result;
	t_token				*remains;
	t_token				*remains2;

	set_error(NO_ERROR);
	if (tokens == NULL)
		return (NULL);
	result = memalloc_or_die(sizeof(t_simple_command));
	result->redirections = parse_redirections(tokens, &remains);
	if (get_error() == NO_ERROR)
	{
		result->assignments = parse_assignments(remains, &remains2);
		if (get_error() == NO_ERROR)
			result->argv = parse_argv(remains2);
		delete_all_tokens(&remains2);
	}
	delete_all_tokens(&remains);
	if (get_error() != NO_ERROR)
		result = NULL; // delete_simple_command(&result);
	return (result);
}
