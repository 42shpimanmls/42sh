#include <libft.h>

void	print_n_char(char c, size_t n)
{
	while (n > 0)
	{
		n--;
		ft_putchar(c);
	}
}
