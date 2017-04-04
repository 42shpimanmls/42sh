#include "libft.h"
#include "shell_env.h"
#include "errors.h"

#include "history_substitutions.h"

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

static void 	remove_head(char **str, char c)
{
	size_t	i;
	char 	*tmp;

	i = 0;
	while ((*str)[i] && (*str)[i] != c)
		i++;
	if (str[i])
	{
		tmp = ft_strsub(*str, i + 1, ft_strlen(*str) - i);
		ft_strdel(str);
		*str = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
}

/*
 	!!:s/ !!:s// !!:s previous substitution
 	if not found substitution failed
 	!!:s/kg removes kg
*/


bool	apply_modifiers(char *modifiers, char **str, t_uint *end)
{
	t_uint 		i;
	bool		should_run;

	i = 0;
	should_run = 1;
	while (modifiers[i]) // invalid read - why ? fix = i < ft_strlen()
	{
		if (modifiers[i] == ':')
		{
			i++;

			// h remove trailing pathname component i.e. what is after last slash
			if (modifiers[i] == 'h')
				remove_tail(str, '/');

			// t remove head, leave tail i.e.  file name
			else if (modifiers[i] == 't')
				remove_head(str, '/');

			// r Remove a trailing suffix of the form ‘.suffix’, leaving the basename.
			else if (modifiers[i] == 'r')
				remove_tail(str, '.');

			// e remove all but the trailing suffix
			else if (modifiers[i] == 'e')
				remove_head(str, '.');

			// p print the command but do not execute it
			else if (modifiers[i] == 'p')
			{
				i++;
				should_run = 0;
			}

			// q quote the substituted word, escaping further substitution

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
				substitute_str(modifiers, str, &i, false);

			// &repeat the previous substitution

			/*
				g
				Cause changes to be applied over the entire event line.
				Used in conjunction with ‘s’, as in gs/old/new/, or with ‘&’.
			*/
			else if (modifiers[i] == 'g')
			{
				// i++;
				if (modifiers[i + 1] == 's')
				{
					i++;
					substitute_str(modifiers, str, &i, true);
				}
			}

			// G Apply the following ‘s’ modifier once to each word in the event.
			// non conclusive test in sh
			else if (modifiers[i] == 'G')
				substitute_words_str(modifiers, str, &i);

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