#include "shell_env.h"

#include "abstract_list.h"
#include "utils.h"
#include "uint.h"
#include "range.h"
#include "errors.h"

#include "history.h"
#include "history_substitutions.h"



char	*get_last_word(char *line)
{
	t_token *words;
	t_token *tmp;
	char 	*word;

	word = NULL;
	if ((words = tokenize_for_substitution(line)))
	{
		tmp = words;
		while (tmp->next)
			tmp = tmp->next;
		word = ft_strdup(tmp->str);
		delete_all_tokens(&words);
	}
	return (word);
}

char	*word_range_collapse(t_token *words, t_uint nb_wds, bool empty_ok)
{
	char	*word_range;

	word_range = ft_strdup(words->str);
	while (nb_wds > 0)
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
		nb_wds--;

	}
	// free words
	return (word_range);
}

char	*get_word_range(char *line, t_range *range)
{
	t_token *words;
	t_uint	nb_wds;
	char 	*str;

	str = NULL;
	if ((words = tokenize_for_substitution(line)))
	{
		print_tokens(words);
		if (range->end < 0)
			range->end += list_count((t_abstract_list *)words);
		nb_wds = range->end - range->start;
		if (!list_goto_n((t_abstract_list **)&words, range->start))
			return (NULL);
		str = word_range_collapse(words, nb_wds, range->empty_ok);
		delete_all_tokens(&words);
	}
	return (str);
}

char	*get_nth_word(char *line, t_uint n)
{
	t_range range;

	range.start = n;
	range.end = n;
	range.empty_ok = false;
	return (get_word_range(line, &range));
}

bool	start_word_designator(char c)
{
	if (c == ':' || c == '^' || c == '%' || c == '*' || c == '-' || c == '$')
		return (true);
	return (false);
}

int 	parse_range(char *str, int *i, t_range *range)
{
	// ‘-y’ abbreviates ‘0-y’
	if (str[*i] == '-')
	{
		range->start = 0;
		if (ft_isdigit(str[(*i) + 1]))
		{
			range->end = ft_atoi(&str[*i + 1]);
			*i += number_len(&str[*i + 1]) + 1;
		}
		else
			range->end = -2;
	}
	else
	{
		range->start = ft_atoi(&str[*i]);
		*i += number_len(&str[*i]);
		if (str[*i] && str[*i] == '-')
		{
			(*i)++;
			if (str[*i] && ft_isdigit(str[*i]))
			{
				range->end = ft_atoi(&str[*i]);
				*i += number_len(&str[*i]);
			}
			//'x-$' = x-last
			else if (str[*i] && str[*i] == '$')
			{
				(*i)++;
				range->end = -1;
			}
			// x- is x-$ but omits the last word
			else
				range->end = -2;
		}
		// x*  = x-$
		else if (str[*i] == '*')
		{
			(*i)++;
			range->end = -2;
		}
	}
	return (0);
}

void	parse_word_designators(char *str, int *i, char **words, t_range *range, char **entry)
{
	/*
		'*' all the words except 0 (1-$)
		It is not an error to use ‘*’ if there is just one word in the event;
		the empty string is returned in that case.
	*/
	if (str[*i] == '*')
	{
		// (*i)++;
		range->start = 1;
		range->end = -1;
		range->empty_ok = true;
	}

	// ^ word 1 (first argument)
	else if (str[*i] == '^')
		range->start = range->end = 1;

	// $ last argument/word
	else if (str[*i] == '$')
	{
		// (*i)++;
		// (*end)++;
		*words = get_last_word(*entry);
		ft_strdel(entry);
		*entry = ft_strdup(*words);
		ft_strdel(words);
		// return (0);
	}

	// % The word matched by the most recent ‘?string?’ search.
	else if (str[*i] == '%')
	{;}
	else if (str[*i] == '-')
	{
		parse_range(str, i, range);
		// range->start = 1;
	}
	(*i)++;
}

int		get_entry_word(char **entry, char *str, t_uint *end) // ret void
{
	int 	i;
	char	*words;
	t_range	range;

	i = 0;
	words = NULL;
	ft_bzero(&range, sizeof(t_range));
	if (start_word_designator(*str))
	{
		if (*str == ':')
		{
			i++;
			if (ft_isdigit(str[i]) || str[i] == '-')
			{
				//  x-y ; x- ; -y  A range of words
				if (ft_strchr(str, '-'))
				{
					if (parse_range(str, &i, &range) < 0)
					{
						words = ft_strnew(1);
						return (0);
					}
				}
				// designator = n => nth word ; n* = n-$
				else
				{
					range.start = ft_atoi(&str[i]);
					if (str[i + number_len(&str[i])] && str[i + number_len(&str[i])] == '*')
					{
						i += number_len(&str[i]) + 1;
						range.end = -1;
					}
					else
						range.end = range.start;
					i += number_len(&str[i]);
				}
			}
			else if (start_word_designator(str[i]))
				parse_word_designators(str, &i, &words, &range, entry);
			else
				return (0);
		}
		else
			parse_word_designators(str, &i, &words, &range, entry);
	}
	/*
		other function
	*/
		(*end) += i;
		if (!words)
		{
			if ((words = get_word_range(*entry, &range)))
			{
				ft_strdel(entry);
				*entry = ft_strdup(words);
				ft_strdel(&words);
			}
			else
			{
				error_builtin(NULL, ft_strsub(str, 0, i), BAD_WD_SPEC); // return err_func
				return (-1);
			}
		}
		return (0);
	}