#include "libft.h"
#include "shell_env.h"
#include "errors.h"

#include "abstract_list.h"
#include "utils.h"
#include "uint.h"

#include "history.h"
#include "history_substitutions.h"

void 	substitute_bang(char **str, char *hist_entry, t_uint *start, t_uint end)
{
	char	*to_sub;

	to_sub = ft_strsub(*str, *start, end - *start);
	find_and_replace(str, to_sub, hist_entry, *start);
	*start = end;
	ft_strdel(&hist_entry);
	ft_strdel(&to_sub);
}

int	 	start_substitution(char **str, t_uint *start, char *hist_entry)
{
	t_uint	end;
	int		should_run;

	end = *start;
	if (!hist_entry)
	{
		if (!(hist_entry = get_history_entry(&(*str)[*start + 1], &end)))
			error_builtin(NULL, ft_strsub(*str, *start, end - *start), EV_NOT_FOUND);
		if ((*str)[end])
			end++;
	}
	else
		end += 2;
	if ((*str)[end] && start_word_designator((*str)[end]))
		get_entry_word(&hist_entry, &(*str)[end], &end);
	if (end < ft_strlen(*str) && (*str)[end] == ':')
		should_run = apply_modifiers(&(*str)[end], &hist_entry, &end);
	if (get_error() == NO_ERROR)
	{
		substitute_bang(str, hist_entry, start, end);
		return (should_run);
	}
	ft_strdel(&hist_entry);
	return (-1);
}

static bool is_blank_equal_ret(char c)
{
	if (is_posix_blank(c) || c == '\n' || c == '=')
		return (1);
	return (0);
}

void		bang_sharp(char **str, t_uint *i, int *should_run)
{
	char *tmp;

	if (*i > 0)
		*should_run = start_substitution(str, i, ft_strsub(*str, 0, *i));
	else
	{
		tmp = ft_strsub(*str, 2, ft_strlen(*str) - 2);
		ft_strdel(str);
		*str = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
}

static void	check_quotes(char const *str, t_uint *i, bool *quoted)
{
	if (str[*i] == '\\')
		(*i)++;
	else if (str[*i] == '\'')
		*quoted = !*quoted;
}

int			history_substitution(char **str)
{
	t_uint		i;
	bool 		quoted;
	int 		should_run;

 	i = 0;
	quoted = 0;
	should_run = 1;
	set_error(NO_ERROR);
	while (i < ft_strlen(*str))
	{
		if (get_error() != NO_ERROR)
			return (-1);
		check_quotes(*str, &i, &quoted);

		// '!' starts a history substitution
		if (is_bang((*str)[i]) && !quoted)
		{
			// !# line typed so far
			if ((*str)[i + 1] && (*str)[i + 1] == '#')
				bang_sharp(str, &i, &should_run);

			// all other cases
			else if (!is_blank_equal_ret((*str)[i + 1]))
				should_run = start_substitution(str, &i, NULL);
		}

		// case [no bang] ˆstr1ˆstr2[ˆ||\n] same as !!:s/str1/str2
		else if (is_circumflex((*str)[i]))
		{
			; // quick_substitution
		}
		if (i < ft_strlen(*str))
			i++;
	}
	ft_putendl(*str);
	return (should_run);
}
