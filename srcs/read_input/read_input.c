#include "shell_env.h"
#include "edit_input.h"
#include "ftsh.h"
#include "utils.h"

static void handle_command_string(t_shell_env *shell_env)
{
	shell_env->input_string = ft_strdup(shell_env->command_string);
	shell_env->should_run = false;
}

static void handle_stdin(t_shell_env *shell_env)
{
	shell_env->input_string = edit_input();
	shell_env->should_run = true;
}

void	read_input()
{
	t_shell_env *shell_env;

	shell_env = get_shell_env();
	if (shell_env->command_string != NULL)
		handle_command_string(shell_env);
	else
		handle_stdin(shell_env);
#ifdef FTSH_DEBUG
	ft_printf("<input_string>\n\"");
	print_non_ascii_str(shell_env->input_string);
	ft_printf("\"\n</input_string>\n");
#endif
	shell_env->last_unmatched = NO_ERROR;
}
