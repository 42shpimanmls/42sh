#include <libft.h>

// le %x du printf de la libft marche pas donc je laisse pour l'instant
#include <stdio.h>

void						print_non_ascii_str(char const *str)
{
	while (*str)
	{
		if (!ft_isprint(*str))
			printf("\\x%x", *str);
		else
			ft_putchar(*str);
		str++;
	}
}
