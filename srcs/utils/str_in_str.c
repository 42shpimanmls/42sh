#include <libft.h>
#include <stdbool.h>
#include "utils.h"
#include "uint.h"

char	*str_in_str(char *find, char *str, t_uint from, bool must_start)
{
	char	*start;

	if (must_start)
		start = str;
	else
	{
		if (!(start = ft_strchr(&str[from], *find)))
			return (NULL);
	}
	if (ft_strnequ(start, find, ft_strlen(find)))
		return (start);
	return (NULL);
}