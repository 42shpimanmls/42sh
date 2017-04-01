#include "libft.h"
#include "shell_env.h"
#include "errors.h"

#include "abstract_list.h"
#include "utils.h"
#include "uint.h"

#include "history.h"
#include "history_substitutions.h"


static char		*get_nth_entry(t_history *history, int n)
{
	if (n == 0 || !history)
		return (NULL);
	else if (n < 0)
	{
		list_goto_last((t_abstract_list **)&history);
		while (n < -1)
		{
			if (!(history = history->prev))
				return (NULL);
			n++;
		}
	}
	else
	{
		while (n > 1)
		{
			if (!(history = history->next))
				return (NULL);
			n--;
		}
	}
	return (ft_strtrim(history->line)); // trim \n
}

static char		*find_in_history(bool must_start, t_history *history, char *str, t_uint *end)
{
	char	*find;
	int 	i;

	i = 0;
	list_goto_last((t_abstract_list **)&history);
	if (must_start)
	{
		while (str[i] && !start_word_designator(str[i]) && !is_posix_blank(str[i]))
			i++;
	}
	else
	{
		while (str[i] && !is_posix_blank(str[i]) && str[i] != '\n' && str[i] != '?')
			i++;
		if (str[i] && (str[i] == '?' || str[i] == '\n'))
			(*end)++;
		(*end)++;
	}
	*end += i;
	find = ft_strsub(str, 0, i);
	while (history)
	{
		if ((must_start && str_in_str(find, history->line, 0, true)) \
			|| (!must_start && str_in_str(find, history->line, 0, false)))
		{
			ft_strdel(&find);
			return (ft_strtrim(history->line)); // \n
		}
		history = history->prev;
	}
	return (NULL);
}

char	*get_history_entry(char *designator, t_uint *end)
{
	t_history	*history;
	int 		n;

	history = get_shell_env()->history;

	/* !! or word designator (':', ‘^’, ‘$’, ‘*’, ‘-’, or ‘%’)  => previous command \
		 (take '-' out of the list?)
	*/

	if (is_bang(*designator) || (start_word_designator(*designator) && *designator != '-'))
	{
		if (is_bang(*designator))
			(*end)++;
		return (get_nth_entry(history, -1));
	}

	// !n command line n   / !-n command n lines back
	else if (ft_isdigit(*designator) || *designator == '-')
	{
		(*end)++;
		n = ft_atoi(designator);
		*end += number_len(designator);
		return (get_nth_entry(history, n));
	}

	//!?str[? or \n] most recent command containing str
	else if (*designator == '?')
		return (find_in_history(false, history, ++designator, end));
	/*
	!!! + store string search in shell_env !!! for :%
	*/

	//!str most recent command that starts with str
	else
		return (find_in_history(true, history, designator, end));
	return (NULL);
}
