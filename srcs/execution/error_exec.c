#include <libft.h>

#define	NSIG 31

char const *get_signal_error(int signum)
{
	static char *defs[NSIG + 1] =
	{
	//DESCRIPTION					
	"None"									,
	"Hangup (POSIX)."						,
	"Interrupt (ANSI)."						,
	"Quit (POSIX)."							,
	"Illegal instruction (ANSI)."			,
	"Trace trap (POSIX)."					,
	"Abort (ANSI)."							,
	"BUS error (4.2 BSD)."					,
	"Floating-point exception (ANSI)."		,
	"Kill, unblockable (POSIX)."			,
	"User-defined signal 1 (POSIX)."		,
	"Segmentation violation (ANSI)."		,
	"User-defined signal 2 (POSIX)."		,
	"Broken pipe (POSIX)."					,
	"Alarm clock (POSIX)."					,
	"Termination (ANSI)."					,
	"Stack fault."							,
	"Child status has changed (POSIX)."		,
	"Continue (POSIX)."						,
	"Stop, unblockable (POSIX)."			,
	"Keyboard stop (POSIX)."				,
	"Background read from tty (POSIX)."		,
	"Background write to tty (POSIX)."		,
	"Urgent condition on socket (4.2 BSD)."	,
	"CPU limit exceeded (4.2 BSD)."			,
	"File size limit exceeded (4.2 BSD)."	,
	"Virtual alarm clock (4.2 BSD)."		,
	"Profiling alarm clock (4.2 BSD)."		,
	"Window size change (4.3 BSD, Sun)."	,
	"I/O now possible (4.2 BSD)."			,
	"Power failure restart (System V)."		,
	"Bad system call."						
	};

	if (signum >= 0 && signum <= NSIG)
	{
		return (defs[signum]);
		// ft_printf("Finished signal -%d --%s\n", signum, defs[signum]);
	}
	return ("");
}
