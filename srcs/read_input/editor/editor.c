#include <libft.h>

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

t_editor *init_editor()
{
	t_editor *new;

	new = memalloc_or_die(sizeof(t_editor));
	new->term = init_term();
	return (new);
}


void	add_to_string(t_string **s, char c)
{
	t_string *new;

	new = memalloc_or_die(sizeof(t_string));
	new->c = c;

	if (!s)
	{
		s = &new;
	}
	else
	{
		list_push_back((t_abstract_list **)s, (t_abstract_list *)new);
	}
}

void print_string(t_string *s)
{
	while (s)
	{
		ft_putchar(s->c);
		s = s->next;
	}
	ft_putchar('\n');
}

char *get_string_from_list(t_string *s)
{
	char 	*str;
	size_t	i;

	str = memalloc_or_die(99); // change count len of list !!!!!!!!
	i = 0;
	while (s)
	{

		str[i] = s->c;
		i++;
		s = s->next;
	}
	str[i] = '\0';
	return (str);
}

void free_string(t_string *s)
{
	while (s)
	{
		s = s->next;
	}
	free(s);
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

char	*ft_read_line()
{
	char buf[EVENT_STR_MAX_LEN + 1];

	ft_memset(buf, 0, EVENT_STR_MAX_LEN + 1);
	read(STDIN_FILENO, buf, EVENT_STR_MAX_LEN);
	return (ft_strdup(buf));
}

void	ft_clear_line(t_string *s)
{
	char *move_left = tgetstr("le", NULL);

	while (s)
	{
		ft_putstr(move_left);
		ft_putstr(tgetstr("cd", NULL));
		s = s->next;
	}
}
