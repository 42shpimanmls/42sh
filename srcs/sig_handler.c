#include "sig_handler.h"
#include "completion.h"
#include <sys/ioctl.h>

void		sig_int(int sig)
{
	(void)sig;
	kill(-2, SIGKILL);
}
