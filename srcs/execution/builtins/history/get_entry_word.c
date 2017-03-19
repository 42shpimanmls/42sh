// #include <stdbool.h>
#include "abstract_list.h"
#include "utils.h"
#include "uint.h"
#include "shell_env.h"

#include "break_input/tokenizer.h"

#include "history.h"

char	*get_last_word(char *line)
{
	t_token *words;

	words = tokenize(line);
	while (words->next)
		words = words->next;
	return (words->str);
}

char	*get_nth_word(char *line, t_uint n)
{
	t_token *words;

	words = tokenize(line);
	while (words && n > 0)
	{
		words = words->next;
		n--;
	}
	if (!words)
		return(NULL);
	return (words->str);
}

bool	start_word_designator(char c)
{
	if (c == ':' || c == '^' || c == '%' || c == '*' || c == '-')
		return (true);
	return (false);
}

char	*get_entry_word(char **entry, char *str, t_uint *end)
{
	int 	i;

	i = 0;
	(void)end;
	(void)entry;
	if (*str == ':')
	{
		;
	}
	return (NULL);
}