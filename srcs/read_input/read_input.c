#include "shell_env.h"
#include "edit_input.h"

static void handle_command_string(t_shell_env *shell_env)
{
	shell_env->input_string = ft_strdup(shell_env->command_string);
	shell_env->should_run = false;
}

static void handle_stdin(t_shell_env *shell_env)
{
	shell_env->input_string = edit_input();
	shell_env->should_run = false;
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
	ft_printf("<input_string>\n\"%s\"\n</input_string>\n", shell_env->input_string);
#endif
}
