
#include "utils.h"
#include "range.h"

#include "break_input/tokenizer.h"
#include "history_substitutions.h"

bool			start_word_designator(char c)
{
	if (c == ':' || c == '^' || c == '%' || c == '*' || c == '-' || c == '$')
		return (true);
	return (false);
}

static char		*get_last_word(char *line)
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

void			parse_word_designators(char *str, int *i, char **words, t_range *range, char **entry)
{
	/*
		'*' all the words except 0 (1-$)
		It is not an error to use ‘*’ if there is just one word in the event;
		the empty string is returned in that case.
	*/
	if (str[*i] == '*')
	{
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
		*words = get_last_word(*entry);
		ft_strdel(entry);
		*entry = ft_strdup(*words);
		ft_strdel(words);
	}

	// % The word matched by the most recent ‘?string?’ search.
	else if (str[*i] == '%')
	{;}
	else if (str[*i] == '-')
		parse_range(str, i, range);
	(*i)++;
}