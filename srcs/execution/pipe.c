#include "pipe.h"
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>

pid_t				enter_subshell(void)
{
	pid_t		fork_ret;

	fork_ret = fork();
	if (fork_ret < 0)
	{
		ft_putendl_fd("42sh: failed to fork", 2);
		exit(EXIT_FAILURE);
	}
	return (fork_ret);
}

t_pipe				*create_pipe(void)
{
	t_pipe		*p;
	int			ret;

	p = memalloc_or_die(sizeof(t_pipe));
	ret = pipe(p->fds);
	if (ret != 0)
		ft_memdel((void**)&p);
	return (p);
}

void				delete_pipe(t_pipe **p)
{
	if (p == NULL)
	{
		ft_putendl_fd("42sh: unexpected null t_pipe** in delete_pipe", 2);
		exit(EXIT_FAILURE);
	}
	if ((*p) == NULL)
		return ;
	close((*p)->fds[0]);
	close((*p)->fds[1]);
	ft_memdel((void**)p);
}

int					pipe_get_read_fd(t_pipe const *p)
{
	if (p == NULL)
		return (-1);
	return (p->fds[0]);
}

int					pipe_get_write_fd(t_pipe const *p)
{
	if (p == NULL)
		return (-1);
	return (p->fds[1]);
}

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
		perror("");
		exit(EXIT_FAILURE);
	}
}

void				wait_for_pipeline()
{
	while(wait(NULL) != -1 && errno != ECHILD)
	{
		
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
