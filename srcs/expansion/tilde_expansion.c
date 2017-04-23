#include "expansion.h"
#include "variable.h"
#include <libft.h>
#include "utils.h"

static bool		has_tilde_prefix(char const *word)
{
	if (*word++ == '~' && (!*word || *word == '/'))
		return (true);
	return (false);
}

char			*tilde_expansion(char const *word)
{
	char	*home_path;
	char	*result;

	if (has_tilde_prefix(word))
	{
		if ((home_path = get_variable("HOME")))
		{
			result = ft_strjoin(home_path, word + 1);
			ft_strdel(&home_path);
			quote_word(&result);
		}
		else
			// HOME not set error? ("If HOME is unset, the results are unspecified")
			result = ft_strdup(word);
	}
	else
		result = (ft_strdup(word));
	return (result);
}
