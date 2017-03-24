#include "execute_syntax_tree.h"
#include "utils.h"
#include <libft.h>

#include <stdio.h>

t_error_id	execute_builtin(t_simple_command *cmd, size_t lvl)
{
	t_error_id				ret;
	t_builtin_def const		*builtin;

	ret = NO_ERROR;
	if (cmd != NULL)
	{
		builtin = get_matching_builtin(cmd->argv[0]);
		if (builtin == NULL)
			return (NO_SUCH_BUILTIN);
		print_n_char(' ', (lvl) * 2);
		dprintf(1, "executing builtin %s\n", builtin->name);
		if (builtin->builtin == NULL)
		{
			print_n_char(' ', (lvl + 1) * 2);
			dprintf(1, "%s is undefined\n", builtin->name);
			return (NO_SUCH_BUILTIN);
		}
		ret = builtin->builtin(ft_tablen(cmd->argv), cmd->argv);
		print_n_char(' ', (lvl) * 2);
		dprintf(1, "done executing builtin %s\n", builtin->name);
	}
	return (ret);
}
