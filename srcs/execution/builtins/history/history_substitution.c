#include "libft.h"
#include "shell_env.h"
#include "errors.h"

#include "abstract_list.h"
#include "utils.h"
#include "uint.h"

#include "history.h"
#include "history_substitutions.h"

/*
[no bang] ˆstr1ˆstr2ˆ last command replacing str1 with str2 (= !!:s/str1/str2)
*/

char	*find_history_event(char *designator, t_uint *end)
{
	t_history	*history;
	int 		n;

	history = get_shell_env()->history;

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
			while (designator[*end] && !is_posix_blank(designator[*end]))
				(*end)++;
		}
		n = ft_atoi(designator);
		while (ft_isdigit(designator[*end]) && !is_posix_blank(designator[*end]))
			(*end)++;
		return (get_nth_entry(history, n));
	}

	//!?str[? or \n] most recent command containing str
	else if (*designator == '?')
	{
		(*end)++;
		return (find_in_history(false, history, ++designator, end));
	}
	// !!! store string search in shell_env !!! for :%

	// !$ last word from last command

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
 // before word designator ':', ‘^’, ‘$’, ‘*’, ‘-’, or ‘%’

int	 	start_substitution(char **str, t_uint *start, char **bang_args)
{
	char	*hist_entry;
	char	*to_sub;
	t_uint	end;

	end = *start;
	// ft_putendl("<bang args> ");
	// ft_puttab(bang_args);
	// ft_putendl("</bang args>\n");
	if (!(hist_entry = find_history_event(bang_args[0], &end)))
	{
		error_builtin(NULL, ft_strsub(*str, *start, end - *start + 1), EV_NOT_FOUND); // RET
		return -1;
	}

	/*debug
	else
	{
		ft_putstr("matched hist_entry = \"");
		ft_putstr(hist_entry);
		ft_putendl("\"");
	}
	*/

	// get_hist_word(&hist_entry);
	// modify_hist(&hist_event);
	to_sub = ft_strsub(*str, *start, end - *start + 1);
	find_and_replace(str, to_sub, hist_entry);
	*start = end;
	return (0);
}

/*
	unless ! is simple-quoted or quoted with backslash
*/

int	history_substition(char **str)
{
	t_uint		i;
	char		**bang_args;

	i = 0;
	while ((*str)[i])
	{
		if (is_bang((*str)[i]))
		{
			// except if newline, \t, space, '=' or '('
			if (!(bang_args = ft_strsplit(&(*str)[i + 1], ':')) || !*bang_args)
				return (-1); // error_builtin(SYNTAX_ERROR)
			start_substitution(str, &i, bang_args);
			// go to end of substituted
			// free modifiers
		}
		else if (is_circumflex((*str)[i]))
		{
			; // quick_substitution
		}
		i++;
	}
	return (0);
}

