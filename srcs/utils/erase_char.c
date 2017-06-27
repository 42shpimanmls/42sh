#include <libft.h>

char	*erase_char(char *str)
{
	if (str[0] != '\0')
		ft_strcpy(str, str + 1);
	return (str);
}
