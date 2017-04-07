#include "libft.h"
#include "shell_env.h"
#include "errors.h"
#include "utils.h"

#include "history_substitutions.h"

// to do: error handling

static char	*get_delimited_str(char *modifier, char delimiter, t_uint *i)
{
	char 	*str;
	char 	*tmp;
	size_t 	len;

	if (!(tmp = ft_strchr(modifier, delimiter)))
	{
		len = ft_strlen(modifier) - 1;
		// -1 because of the \n -> are strings always going to end with \n? does it need to be tested?
		str = ft_strsub(modifier, 0, len);
	}
	else
	{
		len = tmp - modifier;
		str = ft_strsub(modifier, 0, len);
	}
	*i += len;
	return (str);
}

void		perform_substitution(char **str, char *hist_entry, \
								t_uint *start, t_uint end)
{
	char	*to_sub;

	to_sub = ft_strsub(*str, *start, end - *start);
	find_and_replace(str, to_sub, hist_entry, *start);
	*start = end;
	ft_strdel(&hist_entry);
	ft_strdel(&to_sub);
	ft_putstr(*str);
}

void		substitute_str(char *modifier, char **str, t_uint *i, bool repeat)
{
	char 	*to_find;
	char 	*replace;
	char 	delimiter;
	t_uint 	start;

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
		ft_putnbr(*i);
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

int 		quick_substitution(char **str, t_uint *start)
{
	char		*hist_entry;
	t_uint		end;

	end = *start;
	hist_entry = get_nth_entry(get_shell_env()->history, -1);
	substitute_str(&(*str)[end], &hist_entry, &end, false);
	perform_substitution(str, hist_entry, start, end);
	// check error
	return (get_error());
}
