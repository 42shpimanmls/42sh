#include <libft.h>

void	print_n_char_fd(char c, size_t n, int fd)
{
	while (n > 0)
	{
		n--;
		ft_putchar_fd(c, fd);
	}
}

void	print_n_char(char c, size_t n)
{
	print_n_char_fd(c, n, STDOUT_FILENO);
}
