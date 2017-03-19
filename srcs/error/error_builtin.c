#include "errors.h"
#include "libft.h"

static void		ft_putstr_colon(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
}

void		error_builtin(char *builtin, char *error, t_error_id id)
{
	ft_putstr_colon("42sh");
	if (builtin)
		ft_putstr_colon(builtin);
	if (error)
	{
		ft_putstr_colon(error);
		/* necessary for strsub in history_substitution error,
		 might cause abort if forgotten to dup the error in other funcs */
		ft_strdel(&error);
	}
	print_error_msg(id);
	if (id == INVALID_OPTION)
	{
		ft_putstr_colon(builtin);
		ft_putstr_colon("usage");
		print_usage_msg(HISTORY_BUID);
	}
}