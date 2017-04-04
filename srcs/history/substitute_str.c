#include "libft.h"
#include "shell_env.h"
#include "errors.h"
#include "utils.h"

#include "history_substitutions.h"

static char	*get_delimited_str(char *modifier, char delimiter, t_uint *i)
{
	char 	*str;
	char 	*tmp;
	size_t 	len;

	if (!(tmp = ft_strchr(modifier, delimiter)))
	{
		len = ft_strlen(modifier);
		str = ft_strsub(modifier, 0, len);
	}
	else
	{
		len = tmp - modifier;
		str = ft_strsub(modifier, 0, len);
		// (*end)++;
	}
	*i += len;
	return (str);
}

void		substitute_str(char *modifier, char **str, t_uint *i, bool repeat)
{
	char 	*to_find;
	char 	*replace;
	char 	delimiter;
	t_uint 	start;

	(*i)++;
	start = 0;
	delimiter = modifier[(*i)++];
	// + handle quoted
	if (!(to_find = get_delimited_str(&modifier[*i], delimiter, i)))
		ft_putendl("previous substitution");
		// previous_substitution();
	else
	{
		(*i)++;
		replace = get_delimited_str(&modifier[*i], delimiter, i);
		if (modifier[*i] == delimiter && modifier[*i - 1] != delimiter)
			(*i)++;
		if (repeat)
		{
			while (start < ft_strlen(*str))
				start = find_and_replace(str, to_find, replace, start);
		}
		else
			find_and_replace(str, to_find, replace, 0);
		ft_strdel(&to_find);
		ft_strdel(&replace);
	}
}

void		substitute_words_str(char *modifiers, char **str, t_uint *i)
{
	t_token 	*words;
	t_token 	*tmp;

	words = tokenize_for_substitution(*str);
	tmp = words;
	ft_strdel(str);
	while (words)
	{
		substitute_str(modifiers, &words->str, i, false);
		str_join_with_space(str, words->str);
		words = words->next;
	}
	delete_all_tokens(&tmp);
}
