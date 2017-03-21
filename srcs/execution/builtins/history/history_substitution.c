#include "libft.h"
#include "shell_env.h"
#include "errors.h"

#include "abstract_list.h"
#include "utils.h"
#include "uint.h"

#include "history.h"
#include "history_substitutions.h"

void	find_and_replace(char **str, char *to_find, char *replace)
{
	char	*tmp;
	char	*tmp2;
	t_uint	i;

	tmp = str_in_str(to_find, *str, false);
	i = tmp - *str;
	tmp2 = ft_strsub(*str, 0, i);
	tmp = ft_strjoin(tmp2, replace);
	ft_strdel(&tmp2);
	tmp2 = ft_strsub(*str, i + ft_strlen(to_find), ft_strlen(*str) - (i + ft_strlen(to_find)));
	ft_strdel(str);
	*str = ft_strjoin(tmp, tmp2);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
}

int	 	start_substitution(char **str, t_uint *start)
{
	char	*hist_entry;
	char	*to_sub;
	t_uint	end;

	end = *start;
	if (!(hist_entry = get_history_entry(&(*str)[*start + 1], &end)))
	{
		error_builtin(NULL, ft_strsub(*str, *start, end - *start + 1), EV_NOT_FOUND); // RET
		return -1;
	}
	end++;
	/* debug
	 ft_putstr("matched event = \"");
	 ft_putstr(hist_entry);
	 ft_putendl("\"");
	 */
	if (start_word_designator((*str)[end]))
	{
		if (get_entry_word(&hist_entry, &(*str)[end], &end) < 0)
			return (-1); // error
		// if (start_word_designator((*str)[end]))
			// ;// modify_hist(&hist_event);
	}
	to_sub = ft_strsub(*str, *start, end - *start);
	find_and_replace(str, to_sub, hist_entry);
	*start = end;
	return (0);
}

/*
	unless ! is simple-quoted or quoted with backslash
*/

int	history_substitution(char **str) // ret should determine if command runs or not (p modifier)
{
	t_uint		i;

	i = 0;
	while ((*str)[i])
	{
		// '!' starts a history substitution
		if (is_bang((*str)[i]))
		{
			// !# line typed so far
			if ((*str)[i + 1] && (*str)[i + 1] == '#')
			{
				; // dup + join str
			}
			if ((*str)[i + 1] && (*str)[i + 1] != '\n' && (*str)[i + 1] != '\t' \
				 && (*str)[i + 1] != ' ' && (*str)[i + 1] != '=')
				if (start_substitution(str, &i) < 0)
					return (-1);
			// go to end of substituted
		}

		// case [no bang] ˆstr1ˆstr2[ˆ||\n] same as !!:s/str1/str2
		else if (is_circumflex((*str)[i]))
		{
			; // quick_substitution
		}

		else if (start_word_designator((*str)[i]))
		{
			;//start_substitution("!", &i));
			// get_entry_word(get_history_entry("!", &i), &(*str)[i], &i);
			// modifiers
		}
		i++;
	}
	return (0);
}
