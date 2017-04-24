#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include "uint.h"
#include "errors.h"
#include "utils.h"
#include "execution/signal_error_exec.h"
#include <signal.h>

void				wait_for_childs()
{
	int		wstatus;
	t_uchar	estatus;

	set_error(NO_ERROR);
	wstatus = 0;
	while(wait(&wstatus) != -1 && errno != ECHILD)
	{
		if (WIFEXITED(wstatus))
		{
			estatus = WEXITSTATUS(wstatus);
			set_last_exit_status(estatus);
			if (estatus != EXIT_SUCCESS)
				set_error(CHILD_FAILURE);
		}
		if (WIFSIGNALED(wstatus))
		{
			if (WTERMSIG(wstatus) != SIGINT)
				ft_dprintf(STDERR_FILENO, "%s: error signal -%d --%s\n", SHNAME, wstatus, get_signal_error(wstatus)); //test
			// set_last_exit_status(wstatus);
		}
	}
	if (WIFEXITED(wstatus))
		set_last_exit_status(WEXITSTATUS(wstatus));
}

 void	wait_for_last_child(pid_t last_child_pid)
 {
 	int		wstatus;
	t_uchar	estatus;

	set_error(NO_ERROR);

	while (waitpid(last_child_pid, &wstatus, 0) != last_child_pid && !errno)
		;
	if (WIFEXITED(wstatus))
	{
		estatus = WEXITSTATUS(wstatus);
		set_last_exit_status(estatus);
		if (estatus != EXIT_SUCCESS)
			set_error(CHILD_FAILURE);
	}
 }
