#include "expansion.h"
#include <stdlib.h>
#include "strlist.h"
#include "abstract_list.h"
#include <libft.h>

/*
2.6 Word Expansions

This section describes the various expansions that are performed on words. Not all expansions are performed on every word, as explained in the following sections.

Tilde expansions, parameter expansions, command substitutions, arithmetic expansions, and quote removals that occur within a single word expand to a single field. It is only field splitting or pathname expansion that can create multiple fields from a single word. The single exception to this rule is the expansion of the special parameter '@' within double-quotes, as described in Special Parameters.

The order of word expansion shall be as follows:

   1. Tilde expansion (see Tilde Expansion), parameter expansion (see Parameter Expansion), command substitution (see Command Substitution), and arithmetic expansion (see Arithmetic Expansion) shall be performed, beginning to end. See item 5 in Token Recognition.

   2. Field splitting (see Field Splitting) shall be performed on the portions of the fields generated by step 1, unless IFS is null.

   3. Pathname expansion (see Pathname Expansion) shall be performed, unless set -f is in effect.

   4. Quote removal (see Quote Removal) shall always be performed last.

The expansions described in this section shall occur in the same shell environment as that in which the command is executed.

If the complete expansion appropriate for a word results in an empty field, that empty field shall be deleted from the list of fields that form the completely expanded command, unless the original word contained single-quote or double-quote characters.

The '$' character is used to introduce parameter expansion, command substitution, or arithmetic evaluation. If an unquoted '$' is followed by a character that is not one of the following:

   A numeric character

   The name of one of the special parameters (see Special Parameters)

   A valid first character of a variable name

   A <left-curly-bracket> ( '{' )

   A <left-parenthesis>

the result is unspecified.
*/

static t_strlist	*expand_cmd_word(char const *word)
{
	t_strlist	*result;
	char		*str;
	t_strlist	*it;
	char		*tmp;

	result = NULL;
	if (word != NULL)
	{
		str = tilde_expansion(word);
		// tmp = str;
		tmp = parameter_expansion(str);
		ft_strdel(&str);
		str = tmp;
		if (!str)
			return (NULL);
		tmp = command_substition(str);
		ft_strdel(&str);
		if (!tmp)
			return (NULL);
		result = field_splitting(tmp);
		ft_strdel(&tmp);
		it = result;
		while (it != NULL)
		{
			/*str = pathname_expansion(it->str);
			free(it->str);
			*/
			quote_removal(&it->str);
			it = it->next;
		}
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
		fields = expand_cmd_word(*words);
		list_concat((t_abstract_list**)&word_list, (t_abstract_list*)fields);
		words++;
	}
	ft_freetabchar(*words_addr);
	*words_addr = strlist_to_strarray(word_list);
	strlist_delete(&word_list);
}
