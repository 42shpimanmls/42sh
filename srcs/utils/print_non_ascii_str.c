#include <libft.h>
#include <stdio.h>

void						print_non_ascii_str(char const *str)
{
	while (*str)
	{
		if (!ft_isprint(*str))
			printf("\\x%x", *str);
		else
			printf("%c", *str);
		str++;
	}
}
