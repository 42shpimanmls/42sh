#include "errors.h"
#include "libft.h"
#include "uint.h"
#include <stdlib.h>

t_builtin_usage const	*get_builtin_usages()
{
	static t_builtin_usage const usages[BUILTIN_DEF_COUNT] =
	{
			// ID 					// MSG
		{ HISTORY_BUID, 		"history [-c] [-d offset] [n] or history -awrn [filename] or history -ps arg [arg...]"}
	};
	return (usages);
}

void					print_error_msg(t_error_id id)
{
	t_error		const 	*errors;
	t_uint				u;

	u = 0;
	errors = get_error_defs();
	while (u < TOTAL_ERROR_COUNT)
	{
		if (id == errors[u].id)
		{
			ft_putstr("42sh: ");
			ft_putendl(errors[u].msg);
			return;
		}
		u++;
	}
}

void					print_usage_msg(t_builtin_id id)
{
	t_builtin_usage		const 	*usages;
	t_uint						u;

	u = 0;
	usages = get_builtin_usages();
	while (u < BUILTIN_DEF_COUNT)
	{
		if (id == usages[u].id)
		{
			ft_putendl(usages[u].msg);
			return;
		}
		u++;
	}
}
