#include "abstract_list.h"
#include "utils.h"
#include "uint.h"
#include "shell_env.h"

#include "break_input/tokenizer.h"

#include "history.h"

char	*get_last_word(char *line)
{
	t_token *words;

	words = tokenize(line);
	while (words->next)
		words = words->next;
	return (words->str);
}

char	*get_word_range(char *line, t_uint start, t_uint end, bool empty_ok)
{
	t_token *words;
	t_uint	range;
	char	*word_range;

	range = end - start;
	words = tokenize(line);
	if (!list_goto_n((t_abstract_list **)&words, start))
		return (NULL);
	word_range = ft_strdup(words->str);
	ft_putendl(line);
	while (range > 0)
	{
		words = words->next;
		if (!words)
		{
			if (empty_ok)
				return (ft_strnew(1));
			ft_strdel(&word_range);
			return (NULL);
		}
		str_join_with_space(&word_range, words->str);
		range--;

	}
	return (word_range);
}

char	*get_nth_word(char *line, t_uint n)
{
	return (get_word_range(line, n, n, false));
}

bool	start_word_designator(char c)
{
	if (c == ':' || c == '^' || c == '%' || c == '*' || c == '-')
		return (true);
	return (false);
}

int		get_entry_word(char **entry, char *str, t_uint *end)
{
	int 	i;
	char	*words;
	// char	*tmp;

	i = 0;
	if (*str == ':')
	{
		i++;
		if (ft_isdigit(str[i]) || str[i] == '-')
		{
		//  x-y A range of words; ‘-y’ abbreviates ‘0-y’. ; 'x-' and 'x*' abbreviate 'x-$' ;
			if (ft_strchr(str, '-'))
			{
				// ‘-y’ abbreviates ‘0-y’
				if (str[i] == '-')
				{
					if (ft_isdigit(str[++i]))
					{
						words = get_word_range(*entry, 0, ft_atoi(&str[i]) ,false);
						*end += number_len(&str[i]);
					}
					else
						words = ft_strnew(1);
				}
				else
				{
					;
				}

			}
		// designator = n => nth word
/*
			if (!(words = get_nth_word(*entry, ft_atoi(&str[i]))))
			{
				//error_builtin();
				return (-1);
			}
			while (ft_isdigit(str[i]))
				i++;
		}*/
		// ^ word 1 (first argument)
		// $ last argument/word
		// % The word matched by the most recent ‘?string?’ search.
		/*  '*' all the words except 0 (1-$)
			It is not an error to use ‘*’ if there is just one word in the event;
			the empty string is returned in that case. */
		(*end) += i;
	}
	ft_strdel(entry);
	*entry = ft_strdup(words);
	}
	return (0);
}