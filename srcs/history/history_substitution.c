#include "libft.h"
#include "shell_env.h"
#include "errors.h"

#include "abstract_list.h"
#include "utils.h"
#include "uint.h"

#include "history.h"
#include "history_substitutions.h"

void	find_and_replace(char **str, char *to_find, char *replace, t_uint start)
{
	char	*tmp;
	char	*tmp2;
	t_uint	i;

	tmp = str_in_str(to_find, *str, start, false);
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

int	 	start_substitution(char **str, t_uint *start, char *hist_entry)
{
	char	*to_sub;
	t_uint	end;
	bool	should_run;

	end = *start;
	if (!hist_entry)
	{
		if (!(hist_entry = get_history_entry(&(*str)[*start + 1], &end)))
		{
			error_builtin(NULL, ft_strsub(*str, *start, end - *start), EV_NOT_FOUND);
			// + 1
		}
		end++;
	}
	else
		end += 2;
	if (start_word_designator((*str)[end]))
		get_entry_word(&hist_entry, &(*str)[end], &end);
	if ((*str)[end] == ':')
		should_run = apply_modifiers(&(*str)[end], &hist_entry, &end);
	if (get_error() == NO_ERROR)
	{
		to_sub = ft_strsub(*str, *start, end - *start);
		find_and_replace(str, to_sub, hist_entry, *start);
		*start = end;
		return (should_run);
	}
	return (-1);
}

static bool is_blank_equal_ret(char c)
{
	if (is_posix_blank(c) || c == '\n' || c == '=')
		return (1);
	return (0);
}

/*
	unless ! is simple-quoted or quoted with backslash
*/

int	history_substitution(char **str) // ret should be bool -> determine if command runs or not (p modifier)
{
	t_uint		i;
	char		*tmp;
	bool 		quoted;

	i = 0;
	quoted = 0;
	set_error(NO_ERROR);
	while ((*str)[i])
	{
		if ((*str)[i] == '\\')
			i++;
		else if ((*str)[i] == '\'')
		{
			quoted = !quoted;
		}
		// '!' starts a history substitution
		else if (is_bang((*str)[i]) && !quoted)
		{
			// !# line typed so far
			if ((*str)[i + 1] && (*str)[i + 1] == '#')
			{
				if (i > 0)
					start_substitution(str, &i, ft_strsub(*str, 0, i));
				else if (ft_strlen(*str) > 2)
				{
					tmp = ft_strsub(*str, 2, ft_strlen(*str) - 2);
					ft_strdel(str);
					*str = ft_strdup(tmp);
				}
				else
				{
					ft_strdel(str);
					*str = ft_strdup("\n");
				}
			}
			else if (!is_blank_equal_ret((*str)[i + 1]))
			{
				if (start_substitution(str, &i, NULL) < 0) // use errno
					return (-1);
			}
		}

		// case [no bang] ˆstr1ˆstr2[ˆ||\n] same as !!:s/str1/str2
		else if (is_circumflex((*str)[i]))
		{
			; // quick_substitution
		}
		i++;
	}
	return (get_error());
}
