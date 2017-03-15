#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include <unistd.h>
#include <libft.h>
#include <fcntl.h>
#include "edit_input/event_callbacks/event_callback_def.h"

static void	termios_init(void)
{
	struct termios	term;

	if (!isatty(STDOUT_FILENO))
		ft_putendl_fd("42sh: stdout is not a tty", STDERR_FILENO);
	if (tcgetattr(STDOUT_FILENO, &term) != 0)
		ft_putendl_fd("42sh: tcgetattr failed", STDERR_FILENO);
	term.c_lflag &= ~(ICANON | ECHO/* | ISIG*/);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(STDOUT_FILENO, 0, &term) == -1)
		ft_putendl_fd("42sh: tcsetattr failed", STDERR_FILENO);
}

void	event_callback_test(void)
{
	char						buf[EVENT_STR_MAX_LEN + 1];
	ssize_t						ret;
	t_event_callback_def const	*def;

	setbuf(stdout, NULL);
	termios_init();
	ft_putendl("EVENT CALLBACKS TEST, press any key:");
	while ((ret = read(0, buf, EVENT_STR_MAX_LEN)) > 0)
	{
		buf[ret] = '\0';
		ft_putstr("buf:\"");
		print_non_ascii_str(buf);
		ft_putendl("\"");
		def = get_matching_event_callback(buf);
		print_event_callback_def(def);
	}
}
