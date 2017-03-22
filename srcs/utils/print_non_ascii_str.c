#include <libft.h>

// le %x du printf de la libft marche pas donc je laisse pour l'instant
#include <stdio.h>

void						print_non_ascii_char(char c)
{
	if (!ft_isprint(c))
	{
		if (c == '\t')
			ft_putstr("\\t");
		else if (c == '\n')
			ft_putstr("\\n");
		else if (c == '\0')
			ft_putstr("\\0");
		else
			printf("\\x%x", c);
	}
	else if (c == '\\')
		ft_putstr("\\\\");
	else
		ft_putchar(c);
}

void						print_non_ascii_str(char const *str)
{
	while (*str)
	{
		print_non_ascii_char(*str);
		str++;
	}
}
