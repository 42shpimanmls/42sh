#include <libft.h>

void		print_errno_error(int err, char const *pre, char const *post)
{
	ft_putstr_fd("42sh: ", 2);
	if (pre != NULL)
	{
		ft_putstr_fd(pre, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(sys_errlist[err], 2);
	if (post != NULL)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(post, 2);
	}
	ft_putchar_fd('\n', 2);
}