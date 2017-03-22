#include <libft.h>
#include <stdbool.h>
#include "utils.h"

char	*str_in_str(char *find, char *str, bool must_start)
{
	char	*start;

	if (must_start)
		start = str;
	else
	{
		if (!(start = ft_strchr(str, *find)))
			return (NULL);
	}
	if (ft_strnequ(start, find, ft_strlen(find)))
		return (start);
	return (NULL);
}