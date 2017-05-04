#include "shell_env.h"
#include "edit_input.h"
#include "ftsh.h"
#include "utils.h"

static void	handle_command_string(t_shell_env *shell_env)
{
	shell_env->input_string = ft_strdup(shell_env->command_string);
	shell_env->should_run = false;
}

static void	handle_stdin(t_shell_env *shell_env)
{
	char	*tmp;

	if (shell_env->input_string != NULL)
	{
		tmp = shell_env->input_string;
		shell_env->input_string = ft_strjoin(shell_env->input_string,
				edit_input());
		free(tmp);
		shell_env->should_run = true;
	}
	else
		shell_env->input_string = edit_input();
}

void		read_input(void)
{
	t_shell_env *shell_env;

	shell_env = get_shell_env();
	if (shell_env->del_input)
	{
		shell_env->del_input = 0;
		ft_strdel(&shell_env->input_string);
		get_shell_env()->last_unmatched = NO_ERROR;
	}
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
