#include "libft.h"
#include "shell_env.h"
#include "errors.h"

#include "abstract_list.h"
#include "utils.h"
#include "uint.h"

#include "history.h"
#include "history_substitutions.h"

char	*get_history_entry(char *designator, t_uint *end)
{
	t_history	*history;
	int 		n;

	history = get_shell_env()->history;
	// (*end)++;
	// !! previous command
	if (is_bang(*designator))
	{
		(*end)++;
		return (get_nth_entry(history, -1));
	}
	// !n command line n   / !-n command n lines back
	else if (ft_isdigit(*designator) || *designator == '-')
	{
		 (*end)++;
		if (!ft_isdigit(designator[*end]))
		{
			while (designator[*end] && !start_word_designator(designator[*end]) \
					&& !is_posix_blank(designator[*end]))
				(*end)++;
		}
		n = ft_atoi(designator);
		while (ft_isdigit(designator[*end]) && !start_word_designator(designator[*end]) \
				&& !is_posix_blank(designator[*end]))
			(*end)++;
		return (get_nth_entry(history, n));
	}

	//!?str[? or \n] most recent command containing str
	else if (*designator == '?')
		return (find_in_history(false, history, ++designator, end));
	/*
	!!! + store string search in shell_env !!! for :%
	*/

	// !$ = !!:$ = last word from last command
	else if (*designator == '$')
		return (get_nth_entry(history, -1));

	//!str most recent command that starts with str
	else
		return (find_in_history(true, history, designator, end));
	return (NULL);
}

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

	// designators: ':', ‘^’, ‘$’, ‘*’, ‘-’, or ‘%’ => event is last command (!!)
	if (start_word_designator((*str)[end]))
	{
		get_entry_word(&hist_entry, &(*str)[end], &end);
	}
	// modify_hist(&hist_event);
	to_sub = ft_strsub(*str, *start, end - *start);
	find_and_replace(str, to_sub, hist_entry);
	*start = end;
	return (0);
}

/*
	unless ! is simple-quoted or quoted with backslash
*/

int	history_substition(char **str) // ret should determine if command runs or not (p modifier)
{
	t_uint		i;

	i = 0;
	while ((*str)[i])
	{
		// '!' starts a history substitution
		if (is_bang((*str)[i]))
		{
			if ((*str)[i + 1] && (*str)[i + 1] != '\n' && (*str)[i + 1] != '\t' \
				 && (*str)[i + 1] != ' ' && (*str)[i + 1] != '=')
				start_substitution(str, &i);
			// go to end of substituted
			// free modifiers
		}
		// case [no bang] ˆstr1ˆstr2[ˆ||\n] same as !!:s/str1/str2
		else if (is_circumflex((*str)[i]))
		{
			; // quick_substitution
		}
		// designators: ':', ‘^’, ‘$’, ‘*’, ‘-’, or ‘%’ => event is last command (!!)
		else if (start_word_designator((*str)[i]))
		{
			;//get_entry_word(get_history_entry("!", &i), &(*str)[i], &i);
			// modifiers
		}
		i++;
	}
	return (0);
}

