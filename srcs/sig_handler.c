#include "sig_handler.h"

void		sig_int(int sig)
{
	(void)sig;
	kill(-2, SIGKILL);
}
