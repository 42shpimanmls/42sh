#include "pipe.h"
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>

void				create_next_pipe(t_pipeline_state *state)
{
	state->next_pipe = create_pipe();
	if (state->next_pipe == NULL)
	{
		ft_putendl_fd("42sh: failed to create pipe", 2);
		exit(EXIT_FAILURE);
	}
}

void				overwrite_fd(int src, int overwrited)
{
	int		ret;

	ret = dup2(src, overwrited);
	if (ret < 0)
	{
		ft_putstr_fd("42sh: dup2 failed in overwrite_fd: ", 2);
		print_errno_error(errno, "", "");
		exit(EXIT_FAILURE);
	}
}

int					pipe_me_in(t_pipeline_state *state)
{
	pid_t	fork_ret;

	if (state == NULL)
	{
		ft_putendl_fd("42sh: fed null ptr(s) to pipe_me_in", 2);
		exit(EXIT_FAILURE);
	}
	if (state->next_pipe != NULL)
	{
		ft_putendl_fd("42sh: state->next_pipe set while entering pipe_me_in", 2);
		exit(EXIT_FAILURE);
	}
	if (!state->last_cmd)
		create_next_pipe(state);
	fork_ret = enter_subshell();
	if (fork_ret == FORKED_IN_CHILD)
	{
		if (state->prev_pipe != NULL)
			overwrite_fd(pipe_get_read_fd(state->prev_pipe), STDIN_FILENO);
		if (state->next_pipe != NULL)
			overwrite_fd(pipe_get_write_fd(state->next_pipe), STDOUT_FILENO);
		delete_pipe(&state->prev_pipe);
	}
	else
	{
		delete_pipe(&state->prev_pipe);
		state->prev_pipe = state->next_pipe;
		state->next_pipe = NULL;
		state->last_pid = fork_ret;
	}
	return (fork_ret);
}
