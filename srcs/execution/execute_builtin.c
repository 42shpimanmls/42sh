#include "execute_syntax_tree.h"
#include "utils.h"
#include <libft.h>

#include <stdio.h>

t_error_id	execute_builtin(t_simple_command *cmd, size_t lvl)
{
	t_error_id				ret;
	t_builtin_def const		*builtin;
	(void)lvl;

	ret = NO_ERROR;
	if (cmd != NULL)
	{
		if (ft_strcmp(cmd->argv[0], "env") == 0)
			ret = builtin_env(ft_tablen(cmd->argv), cmd->argv, cmd);
		else
		{
			builtin = get_matching_builtin(cmd->argv[0]);
			if (builtin == NULL)
				return (NO_SUCH_BUILTIN);
			set_variable("_", builtin->name, false);
			#ifdef FTSH_DEBUG
			print_n_char_fd(' ', (lvl) * 2, 2);
			dprintf(2, "executing builtin %s\n", builtin->name);
			#endif
			if (builtin->builtin == NULL)
			{
			#ifdef FTSH_DEBUG

				print_n_char_fd(' ', (lvl + 1) * 2, 2);
				dprintf(2, "%s is undefined\n", builtin->name);
			#endif

				return (NO_SUCH_BUILTIN);
			}
			ret = builtin->builtin(ft_tablen(cmd->argv), cmd->argv);
			set_variable("_", cmd->argv[ft_tablen(cmd->argv) - 1], false);
			#ifdef FTSH_DEBUG
			print_n_char_fd(' ', (lvl) * 2, 2);
			dprintf(2, "done executing builtin %s, %s\n", builtin->name, ret == NO_ERROR ? "ok" : "error");
			#endif
		}
	}
	set_last_exit_status(ret == NO_ERROR ? 0 : 1);
	return (ret);
}
