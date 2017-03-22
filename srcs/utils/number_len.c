#include <libft.h>

size_t	number_len(char *str)
{
	size_t i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	return (i);
}