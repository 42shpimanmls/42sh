#include "expansion.h"
#include "strlist.h"
#include <stdlib.h>
#include <libft.h>
#include <stdio.h>
#include "range.h"
#include "utils.h"
#include "abstract_list.h"


static void		next_ret_posix_blank(char *word, int *i)
{
	while (word[*i] && (!is_posix_blank(word[*i]) && word[*i] != '\n'))
		(*i)++;
}

static void		skip_posix_blanks(char *word, int *i)
{
	while (word[*i] && (is_posix_blank(word[*i]) || word[*i] == '\n'))
		(*i)++;
}

static void		add_field(char *word, t_strlist **result, t_range *delimit, size_t pos)
{
	char		*tmp;
	t_strlist	*new;

	tmp = ft_strsub(word, delimit->start, delimit->end - delimit->start);
	#ifdef EXPANSION_DEBUG
		ft_printf("Adding field, str: %s\n", tmp);
	#endif
	new = strlist_construct(tmp, false);
	list_push_at_pos(pos, (t_abstract_list **)result, (t_abstract_list *)new);
	// Each occurrence in the input of an IFS character that is not IFS white space,
	// along with any adjacent IFS white space, shall delimit a field, as described previously.
	// Non-zero-length IFS white space shall delimit a field
	skip_posix_blanks(word, &delimit->end);
	delimit->start = delimit->end;
	ft_strdel(&tmp);
}

/*
**	scan the results of expansions and substitutions
** 	that did not occur in double-quotes and split into fields
**	(marked with the flag "to_split")
*/

// TO DO: double quote handling, white space fields (see comment above)

void field_splitting(t_strlist **l_addr)
{
	t_strlist	*result;
	char		*tmp;
	t_range		delimit;
	size_t		pos;
	size_t		to_del;

	pos = 0;
	result = *l_addr;
	ft_bzero(&delimit, sizeof(t_range));
	while (result)
	{
		if (result->to_split && result->str != NULL)
		{
			to_del = pos;
			tmp = ft_strtrim(result->str);
			while (tmp && tmp[delimit.end])
			{
				pos++;

				next_ret_posix_blank(tmp, &delimit.end);
				#ifdef EXPANSION_DEBUG
					printf("delimit_end: %d\n delimit_start: %d\n", delimit.end, delimit.start);
				#endif
				add_field(tmp, l_addr, &delimit, pos);
				#ifdef EXPANSION_DEBUG
					ft_putendl("FIELD ADDED");
				#endif
			}
			list_pop_at_pos(to_del, (t_abstract_list **)l_addr);
		}
		pos++;
		result = result->next;
	}
}
