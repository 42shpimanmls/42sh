#include <libft.h>

# include <term.h>
# include <termios.h>
# include <curses.h>

# define SHNAME "sh"
# define MAX_READ_TERM 4

#include "read_input/event_callbacks/event_callback_def.h"
#include "utils.h"



int		ft_start_termcaps(void)
{
	struct termios	term;
	char			*env;

	env = getenv("TERM");
	if (!env || tgetent(NULL, env) == ERR ||
		tcgetattr(0, &term) == -1)
	{
		ft_dprintf(2, "%s: I need a variable \"TERM\"\n", SHNAME);
		exit(-1);
	}
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	return (1);
}

int		ft_close_termcaps(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag = (ICANON | ECHO | ISIG);
	if (tcsetattr(0, 0, &term) == -1)
		return (-1);
	return (1);
}

char	*ft_read_line()
{
	char buf[MAX_READ_TERM + 1];

	ft_memset(buf, 0, MAX_READ_TERM + 1);
	read(STDIN_FILENO, buf, MAX_READ_TERM);
	return (ft_strdup(buf));
}

char *edit_input()
{
	//TERMCAPS
	char *line = NULL;

	ft_start_termcaps();

	char						buf[EVENT_STR_MAX_LEN + 1];
	ssize_t						ret;
	t_event_callback_def const	*def;

	setbuf(stdout, NULL);
	// termios_init();
	ft_putendl("EVENT CALLBACKS TEST, press any key:");
	while ((ret = read(0, buf, EVENT_STR_MAX_LEN)) > 0)
	{
		buf[ret] = '\0';
		ft_putstr("buf:\"");
		print_non_ascii_str(buf);
		ft_putendl("\"");
		def = get_matching_event_callback(buf);
		print_event_callback_def(def);
		if (def)
		{
			// Execute action
			ft_printf("DEFINED\n");
		}
		else
		{
			// Add to line
			ft_printf("NOT DEFINED\n");
		}
	}
	
	ft_close_termcaps();

	return (line);	
}
