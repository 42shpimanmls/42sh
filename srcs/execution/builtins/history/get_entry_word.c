#include "shell_env.h"

#include "abstract_list.h"
#include "utils.h"
#include "uint.h"
#include "range.h"

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

char	*get_word_range(char *line, t_range *range, bool empty_ok)
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
			if (empty_ok)
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
	return (get_word_range(line, &range, false));
}

bool	start_word_designator(char c)
{
	if (c == ':' || c == '^' || c == '%' || c == '*' || c == '-')
		return (true);
	return (false);
}

t_range	*parse_range(char *str, int *i)
{
	t_range	*range;

	range = memalloc_or_die(sizeof(t_range));
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
			return (NULL);
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
			else if (str[*i] && str[*i] == '*')
			{
				(*i)++;
				range->end = -1;
			}
			else
				range->end = -2;
		}
	}
	return (range);
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
	// t_uint	start;
	t_range	*range;

	i = 0;
	if (start_word_designator(*str))
	{
		if (*str == ':')
			i++;
		if (ft_isdigit(str[i]) || str[i] == '-')
		{

			/*
			func parse_range
			*/

		//  x-y ; x- ; x* ; -y  A range of words
			if (ft_strchr(str, '-'))
			{
				if (!(range = parse_range(str, &i)))
					words = ft_strnew(1);
				else
				{
					print_range(range);
					words = get_word_range(*entry, range ,false);
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