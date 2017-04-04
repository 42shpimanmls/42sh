#include "parse_input/syntax_tree.h"
#include "errors.h"
#include "utils.h"
#include <libft.h>
#include "execute_syntax_tree.h"
#include "pipe.h"
#include "errno.h"
#include <stdio.h>
#include "redirection.h"


t_error_id	execute_file(t_simple_command *cmd, size_t lvl)
{
	print_n_char_fd(' ', (lvl) * 2, 2);
	dprintf(2, "executing file %s\n", cmd->argv[0]);
	if (enter_subshell() == FORKED_IN_CHILD)
	{
		execvp(cmd->argv[0], cmd->argv);
		print_n_char_fd(' ', (lvl) * 2, 2);
		dprintf(2, "error while executing file: ");
		perror("");
		return (errno);
	}
	else
	{
		wait_for_childs();
		return (NO_ERROR);
	}
}

t_error_id	execute_simple_command(t_simple_command *cmd, size_t lvl)
{
	t_error_id	ret;
	extern char	**environ;
	char		**environ_backup;
	int 		*stdin_out_backup;

	ret = NO_ERROR;
	if (cmd != NULL)
	{
		// EXECUTION CORE
		//expand_words(&cmd->argv);
		stdin_out_backup = save_stdin_stdout();
		ret = redirect(cmd->redirections);
		//expand_assignments_values(cmd->assignments);
		if (ret != NO_ERROR)
			return (ret);
		environ_backup = environ;
		environ = get_variables_for_execution(cmd->assignments);
		ret = execute_builtin(cmd, lvl);
		if (ret == NO_SUCH_BUILTIN)
			ret = execute_file(cmd, lvl);
		ft_freetabchar(environ);
		environ = environ_backup;
		restore_stdin_stdout(stdin_out_backup);
	}
	return (ret);
}

t_error_id	execute_pipeline(t_simple_command *pipeline, size_t lvl)
{
	t_error_id			ret;
	t_pipeline_state	pipeline_state;

	if (pipeline == NULL)
		return (NO_ERROR);
	if (pipeline->next == NULL)
		return (execute_simple_command(pipeline, lvl));
	print_n_char_fd(' ', (lvl) * 2, 2);
	dprintf(2, "executing pipeline\n");
	ft_bzero(&pipeline_state, sizeof(t_pipeline_state));
	ret = NO_ERROR;
	while (pipeline != NULL)
	{
		if (pipeline->next == NULL)
			pipeline_state.last_cmd = true;
		if (pipe_me_in(&pipeline_state) == FORKED_IN_CHILD)
		{
			ret = execute_simple_command(pipeline, lvl + 1);
			if (ret == NO_ERROR)
				exit(EXIT_SUCCESS);
			else
				exit(EXIT_FAILURE);
		}
		pipeline = pipeline->next;
	}
	wait_for_childs();
	print_n_char_fd(' ', (lvl) * 2, 2);
	dprintf(2, "done executing pipeline, %s\n", pipeline_state.last_ret == NO_ERROR ? "ok" : "error");
	return (ret);
}
