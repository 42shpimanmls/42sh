#include "shell_env.h"
#include "edit_input.h"

static void handle_command_string(t_shell_env *shell_env)
{
	ft_memdel((void**)&shell_env->input_string);
	if (!shell_env->should_keep_reading)
		shell_env->input_string = shell_env->command_string;
	else
		shell_env->should_run = false;
}

static void handle_stdin(t_shell_env *shell_env)
{
	ft_memdel((void**)&shell_env->input_string);
	// if (in_a_terminal)
		shell_env->input_string = edit_input();
	// else
		// shell_env->input = get_next_line(stdin)
}

void	read_input()
{
	t_shell_env *shell_env;

	shell_env = get_shell_env();
	if (shell_env->command_string != NULL)
		handle_command_string(shell_env);
	else
		handle_stdin(shell_env);
	ft_printf("<input_string>\n\"%s\"\n</input_string>\n", shell_env->input_string);
}
