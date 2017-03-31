#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

void				wait_for_childs()
{
	while(wait(NULL) != -1 && errno != ECHILD)
	{

	}
}
