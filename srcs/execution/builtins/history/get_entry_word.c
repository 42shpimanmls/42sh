#include "shell_env.h"

#include "abstract_list.h"
#include "utils.h"
#include "uint.h"
#include "range.h"
#include "errors.h"

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

char	*get_word_range(char *line, t_range *range)
{
	t_token *words;
	t_uint	nb_wds;
	char	*word_range;

	words = tokenize(line);
	if (range->end < 0)
	{
		range->end = list_count((t_abstract_list *)words) + range->end;
	}
	nb_wds = range->end - range->start;
	if (!list_goto_n((t_abstract_list **)&words, range->start))
		return (NULL);
	word_range = ft_strdup(words->str);
	while (nb_wds > 0)
	{
		words = words->next;
		if (!words)
		{
			if (range->empty_ok)
				return (ft_strnew(1));
			ft_strdel(&word_range);
			return (NULL);
		}
		str_join_with_space(&word_range, words->str);
		nb_wds--;

	}
	return (word_range);
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
		if (ft_isdigit(str[++(*i)]))
		{
			range->start = 0;
			range->end = ft_atoi(&str[*i]);
			*i += number_len(&str[*i]);
		}
		else
			return (-1);
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
		// 'x-' and 'x*' abbreviate 'x-$' ; 'x-' omits the last word
			else if (str[*i] && str[*i] == '$')
			{
				(*i)++;
				range->end = -1;
			}
			else
			{
				if (str[*i] == '*')
					(*i)++;
				range->end = -2;
			}
		}
	}
	return (0);
}

void	print_range(t_range *range)
{
	ft_putendl("<range>");
	ft_putendl("start: ");
	ft_putnbr(range->start);
	ft_putchar('\n');
	ft_putendl("end: ");
	ft_putnbr(range->end);
	ft_putchar('\n');
	ft_putendl("</range>");
}

int		get_entry_word(char **entry, char *str, t_uint *end)
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
				//  x-y ; x- ; x* ; -y  A range of words
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
						i++;
						range.end = -1;
					}
					else
						range.end = range.start;
					i += number_len(&str[i]);
				}
			}
		}
			// ^ word 1 (first argument)
		if (str[i] == '^')
			range.start = range.end = 1;

			// $ last argument/word
		else if (str[i] == '$')
		{
			(*end)++;
			words = get_last_word(*entry);
			ft_strdel(entry);
			*entry = ft_strdup(words);
			ft_strdel(&words);
			return (0);
		}

		// % The word matched by the most recent ‘?string?’ search.
		else if (str[i] == '%')
			;

		/*  '*' all the words except 0 (1-$)
			It is not an error to use ‘*’ if there is just one word in the event;
			the empty string is returned in that case. */
			else if (str[i] == '*')
			{
				range.start = 1;
				range.end = -1;
				range.empty_ok = true;
			}

			i++;
		}
		(*end) += i;
		// }
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
		return (0);
	}