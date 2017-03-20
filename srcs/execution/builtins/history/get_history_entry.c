#include "libft.h"
#include "shell_env.h"
#include "errors.h"

#include "abstract_list.h"
#include "utils.h"
#include "uint.h"

#include "history.h"
#include "history_substitutions.h"


char	*get_nth_entry(t_history *history, int n)
{
	if (n == 0)
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
	return (ft_strdup(history->line));
}

char	*find_in_history(bool must_start, t_history *history, char *str, t_uint *end)
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
		if ((must_start && str_in_str(find, history->line, true)) \
			|| str_in_str(find, history->line, false))
		{
			ft_strdel(&find);
			return (ft_strdup(history->line));
		}
		history = history->prev;
	}
	return (NULL);
}