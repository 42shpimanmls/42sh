#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include "errors.h"

void				wait_for_childs()
{
	int		wstatus;

	set_error(NO_ERROR);
	while(wait(&wstatus) != -1 && errno != ECHILD)
	{
		if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) != EXIT_SUCCESS)
			set_error(CHILD_FAILURE);
	}
}
