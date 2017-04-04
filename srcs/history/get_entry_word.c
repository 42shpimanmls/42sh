#include "uint.h"
#include "range.h"

#include "history_substitutions.h"

static void		entry_to_words(char *words, char **entry, t_range range, char *str, int i)
{
	if (!words)
	{
		if ((words = get_word_range(*entry, &range)))
		{
			ft_strdel(entry);
			*entry = ft_strdup(words);
			ft_strdel(&words);
		}
		else
			error_builtin(NULL, ft_strsub(str, 0, i), BAD_WD_SPEC);
	}
}

void			get_entry_word(char **entry, char *str, t_uint *end) // ret void
{
	int 	i;
	char	*words;
	t_range	range;

	i = 0;
	words = NULL;
	ft_bzero(&range, sizeof(t_range));
	if (start_word_designator(*str))
	{
		if (*str == ':')
		{
			i++;
			if (ft_isdigit(str[i]) || str[i] == '-')
				range_selection(str, &i, &range, &words);
			else if (start_word_designator(str[i]))
				parse_word_designators(str, &i, &words, &range, entry);
			else
				return;
		}
		else
			parse_word_designators(str, &i, &words, &range, entry);
	}
	(*end) += i;
	entry_to_words(words, entry, range, str, i);
}