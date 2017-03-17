# include <libft.h>
# include <term.h>
# include <termios.h>
# include <curses.h>

# include "utils.h"
# include "abstract_list.h"
# include "read_input/editor/editor.h"
# include "read_input/event_callbacks/event_callback_def.h"

# define SHNAME "sh"

t_term *init_term()
{
	t_term *new;

	new = memalloc_or_die(sizeof(t_term));
	new->move_left = tgetstr("le", NULL);
	new->move_right = tgetstr("nd", NULL);
	new->hide_cursor = tgetstr("vi", NULL);
	new->show_cursor = tgetstr("ve", NULL);
	return (new);
}

void	ft_start_termcaps(void)
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
	term.c_lflag &= ~(ICANON | ECHO | ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
	{
		ft_dprintf(2, "%s: Termcap is lost\n", SHNAME);
		exit(-1);
	}
}

void	ft_close_termcaps(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
	{
		ft_dprintf(2, "%s: Termcap is lost\n", SHNAME);
		exit(-1);
	}
	term.c_lflag = (ICANON | ECHO | ISIG);
	if (tcsetattr(0, 0, &term) == -1)
	{
		ft_dprintf(2, "%s: Termcap is lost\n", SHNAME);
		exit(-1);
	}
}
