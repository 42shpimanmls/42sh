#include "expansion.h"
#include <stdlib.h>
#include "strlist.h"
#include "abstract_list.h"
#include <libft.h>
#include "errors.h"
#include "utils.h"

static t_strlist	*expand_cmd_word(t_strlist *result, char *str,
				t_strlist *it, char *tmp)
{
	tmp = parameter_expansion(str);
	ft_strdel(&str);
	str = tmp;
	if (!str)
		return (NULL);
	tmp = command_substition(str);
	ft_strdel(&str);
	if (!tmp)
		return (NULL);
	set_error(NO_ERROR);
	result = field_splitting(tmp);
	ft_strdel(&tmp);
	it = result;
	while (it != NULL)
	{
		quote_removal(&it->str);
		it = it->next;
	}
	return (result);
}

void				expand_cmd_words(char ***words_addr)
{
	char		**words;
	t_strlist	*fields;
	t_strlist	*word_list;

	words = *words_addr;
	word_list = NULL;
	while (*words != (char*)NULL)
	{
		if (*words == NULL)
			fields = NULL;
		else
			fields = expand_cmd_word(
				NULL, tilde_expansion(*words), NULL, NULL);
		list_concat((t_abstract_list**)&word_list, (t_abstract_list*)fields);
		words++;
	}
	ft_freetabchar(*words_addr);
	*words_addr = strlist_to_strarray(word_list);
	strlist_delete(&word_list);
	if (*words_addr && **words_addr)
		set_error(NO_ERROR);
}
