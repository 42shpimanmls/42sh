#include "abstract_list.h"
#include "utils.h"
#include "range.h"

#include "history_substitutions.h"

/*
** !! to fix: !!-2 no \n
*/

void		range_selection(char *str, int *i, t_range *range, char **words)
{
	if (ft_strchr(str, '-'))
	{
		if (parse_range(str, i, range) < 0)
		{
			*words = ft_strnew(1);
			return ;
		}
	}
	else
	{
		range->start = ft_atoi(&str[*i]);
		if (str[*i + number_len(&str[*i])] && \
			str[*i + number_len(&str[*i])] == '*')
		{
			*i += number_len(&str[*i]) + 1;
			range->end = -1;
		}
		else
			range->end = range->start;
		*i += number_len(&str[*i]);
	}
}

static char	*word_range_collapse(t_token *words, t_uint nb_wds, bool empty_ok)
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
	return (word_range);
}

char		*get_word_range(char *line, t_range *range)
{
	t_token *words;
	t_uint	nb_wds;
	char	*str;
	t_token	*tmp;

	str = NULL;
	if ((words = tokenize_for_substitution(line)))
	{
		tmp = words;
		if (range->end < 0)
			range->end += list_count((t_abstract_list *)words);
		nb_wds = range->end - range->start;
		if (!list_goto_n((t_abstract_list **)&words, range->start))
		{
			delete_all_tokens(&tmp);
			return (NULL);
		}
		str = word_range_collapse(words, nb_wds, range->empty_ok);
		delete_all_tokens(&tmp);
	}
	return (str);
}
