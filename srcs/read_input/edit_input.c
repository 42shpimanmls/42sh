#include <libft.h>

# include <term.h>
# include <termios.h>
# include <curses.h>

# define SHNAME "sh"
# define MAX_READ_TERM 4

#include "read_input/event_callbacks/event_callback_def.h"

#include "utils.h"
#include "abstract_list.h"


typedef struct			s_string
{
	struct s_string		*next;
	struct s_string		*prev;
	char				c;
}						t_string;


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
		// free(s->c);
		s = s->next;
	}
	free(s);
}

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

void	ft_clear_line(t_string *s)
{
	char *move_left = tgetstr("le", NULL);

	while (s)
	{
		ft_putstr(move_left);
		ft_putstr(tgetstr("ce", NULL));
		s = s->next;
	}
	// while (t->i-- > 0)
		// ft_putstr(e->move_left);
	// ft_putstr(tgetstr("ce", NULL));
}

// void	ft_put_line(t_term *t, char *line)
// {
// 	ft_putstr(line);
// 	ft_putstr(tgetstr("cd", NULL));
// 	t->i = ft_strlen(line);
// 	t->imax = t->i - 1;
// 	free(t->res);
// 	t->res = ft_strdup(line);
// }

char *edit_input()
{
	//TERMCAPS
	char		*line;
	t_string	*s;

	line = NULL;
	s = NULL;

	ft_start_termcaps();

	char						buf[EVENT_STR_MAX_LEN + 1];
	ssize_t						ret;
	t_event_callback_def const	*def;

	while ((ret = read(0, buf, EVENT_STR_MAX_LEN)) > 0)
	{
		buf[ret] = '\0';
		def = get_matching_event_callback(buf);
		// print_event_callback_def(def);
		if (def)
		{
			if (def->id == NEWLINE_EVID)
			{
				break ;
			}
		}
		else
		{
			if (buf[0])
			{
				add_to_string(&s, buf[0]);
			}
		}
		ft_clear_line(s);
		line = get_string_from_list(s);
		ft_putstr(line);
		free(line);
	}
	
	ft_close_termcaps();
	line = get_string_from_list(s);
	free_string(s);
	return (line);	
}
