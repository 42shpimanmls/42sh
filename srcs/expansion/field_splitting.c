#include "expansion.h"
#include "strlist.h"
#include <stdlib.h>
#include <libft.h>
#include <stdio.h>

t_strlist		*field_splitting(char const *word)
{
	char		**array;
	char		**it;
	t_strlist	*result;

	// UGLY UGLY TEMPORARY
	result = NULL;
	array = ft_strsplit(word, ' ');
	it = array;
	while (*it != (char *)NULL)
	{
		strlist_append(&result, *it);
		it++;
	}
	ft_freetabchar(array);
	return (result);
}
