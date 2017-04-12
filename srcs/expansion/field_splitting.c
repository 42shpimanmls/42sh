#include "expansion.h"
#include "strlist.h"
#include <stdlib.h>
#include <libft.h>
#include <stdio.h>
#include "range.h"
#include "utils.h"

static void		next_posix_blank(char *word, int *i)
{
	while (word[*i] && !is_posix_blank(word[*i]))
		(*i)++;
}

static void		skip_posix_blanks(char *word, int *i)
{
	while (word[*i] && is_posix_blank(word[*i]))
		(*i)++;
}

static void		add_field(char *word, t_strlist **result, t_range *delimit)
{
	char	*tmp;

	tmp = ft_strsub(word, delimit->start, delimit->end);
	strlist_append(result, tmp);
	skip_posix_blanks(word, &delimit->end);
	delimit->start = delimit->end;
	ft_strdel(&tmp);
}

t_strlist		*field_splitting(char const *word)
{
	t_strlist	*result;
	char		*tmp;
	t_range		delimit;

	result = NULL;
	ft_bzero(&delimit, sizeof(t_range));
	if (word != NULL)
	{
		tmp = ft_strtrim(word);
		while (tmp && tmp[delimit.end])
		{
			next_posix_blank(tmp, &delimit.end);
			add_field(tmp, &result, &delimit);
		}
	}
	return (result);
}
