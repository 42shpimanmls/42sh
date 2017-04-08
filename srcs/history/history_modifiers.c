#include "libft.h"
#include "shell_env.h"
#include "errors.h"

#include "history_substitutions.h"

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
 	if not found substitution failed
*/

bool	apply_modifiers(char *modifiers, char **str, t_uint *end)
{
	t_uint 		i;
	bool		should_run;

	i = 0;
	should_run = 1;
	while (modifiers[i])
	{
		if (modifiers[i] == ':')
		{
			i++;
			if (ft_strchr("htre", modifiers[i]))
				trimming_modifiers(modifiers[i], str, &i);

			// p print the command but do not execute it
			else if (modifiers[i] == 'p')
			{
				i++;
				should_run = 0;
			}

			// q single quote the substituted word, escaping further substitution
			else if (modifiers[i] == 'q')
				;

			// Quote the substituted words as with ‘q’,
			//but break into words at spaces, tabs, and newlines.

			/*
				s/old/new/
				Substitute new for the first occurrence of old in the event line.
				Any delimiter may be used in place of ‘/’.
				The final delimiter is optional if it is the last character on the input line.

				TO DO:
				The delimiter may be quoted in old and new with a single backslash.
				If ‘&’ appears in new, it is replaced by old.
				A single backslash will quote the ‘&’.

			*/
			else if (modifiers[i] == 's')
			{
				i++;
				substitute_str(modifiers, str, &i, false);
			}

			// &repeat the previous substitution
			else if (modifiers[i] == '&')
			{
				i++;
				replace_and_repeat(&get_shell_env()->history.last_subst, str);
			}

			/*
				g Cause changes to be applied over the entire event line.
				G Apply the following ‘s’ modifier once to each word in the event.
				Used in conjunction with ‘s’, as in gs/old/new/, or with ‘&’.
			*/
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
		{
			(*end) += i;
			return (should_run);
		}
	}
	(*end) += i;
	return (should_run);
}