#include "libft.h"
#include "shell_env.h"
#include "errors.h"

#include "history_substitutions.h"
#include "string_substitution.h"

/*
**	removes *str's trailing pathname component
**	i.e. what is after last slash
*/

static void	remove_tail(char **str, char c)
{
	size_t	i;
	char 	*tmp;

	i = ft_strlen(*str);
	while (i > 0 && (*str)[i] != c)
		i--;
	if (i > 0)
	{
		tmp = ft_strsub(*str, 0, i);
		ft_strdel(str);
		*str = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
}

/*
**	removes *str's head
**	i.e. what is before last slash
*/

static void 	remove_head(char **str, char c)
{
	size_t	i;
	char 	*tmp;

	i = 0;
	while ((tmp = ft_strchr(*str, c)))
	{
		i = tmp - *str;
		if (str[i])
		{
			tmp = ft_strsub(*str, i + 1, ft_strlen(*str) - i);
			ft_strdel(str);
			*str = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
	}
}

/*
**	h removes the trailing pathname (/pathname)
**	t keeps only the trailing pathname
**	r removes a trailing suffix (.suffix)
**	e removes all but the trailing suffix
*/

void	trimming_modifiers(char modifier, char **str, t_uint *i)
{
	if (modifier == 'h')
		remove_tail(str, '/');
	else if (modifier == 't')
		remove_head(str, '/');
	else if (modifier == 'r')
		remove_tail(str, '.');
	else if (modifier == 'e')
		remove_head(str, '.');
	(*i)++;
}

/*
**	p prints the substituted command without executing it
**	q quotes the substituted string
**	x breaks the substituted string into words at \n sp \t
**		then quotes them
**	s/old/new[/] Substitutes new for the first occurrence of old in the event line.
**				 Any delimiter may be used in place of ‘/’.
**				 Final delimiter is optional if last character on the input line.
**				 If '&' appears in new, it is replaced by old
**				 A single backslash quotes the delimiter and '&'
**	[gG]s/old/new apply substitution to whole string (g) or once each word (G)
**	& repeats previous substitution
*/

bool	apply_modifiers(char *modifiers, char **str, t_uint *end, bool *quote)
{
	t_uint 		i;
	bool		should_run;

	i = 0;
	should_run = 1;
	*quote = 0;
	while (modifiers[i])
	{
		if (modifiers[i] == ':')
		{
			i++;
			if (ft_strchr("htre", modifiers[i]))
				trimming_modifiers(modifiers[i], str, &i);
			else if (modifiers[i] == 'p')
			{
				i++;
				should_run = 0;
			}
			else if (modifiers[i] == 'q')
			{
				i++;
				*quote = 1;
			}
			else if (modifiers[i] == 'x')
			{
				quote_per_word(str);
				i++;
			}
			else if (modifiers[i] == 's')
			{
				i++;
				substitute_str(modifiers, str, &i, false);
			}
			else if (modifiers[i] == '&')
			{
				i++;
				replace_and_repeat(&get_shell_env()->history.last_subst, str);
			}
			else if (modifiers[i] == 'g' || modifiers[i] == 'G')
			{
				i++;
				if (modifiers[i] == 's')
				{
					i++;
					if (modifiers[i - 2] == 'g')
						substitute_str(modifiers, str, &i, true);
					else
						substitute_words_str(modifiers, str, &i);
				}
			}
			else
				return (should_run);
		}
		else
			break ;
	}
	(*end) += i;
	return (should_run);
}