#include "completion.h"

static void		increase_tabindex(int inc)
{
	t_tabinfo	*inf;
	int			len;

	inf = get_tabinfo();
	len = list_count((t_abstract_list*)inf->list);
	inf->selected_index += inc;
	if (inf->selected_index >= len)
		inf->selected_index -= len;
	else if (inf->selected_index < 0)
		inf->selected_index += len;
}

void		tab_down(t_editor *ed, char *line)
{
	//update_winsize(ed);
	increase_tabindex(1);
	tab_display(ed, line, get_tabinfo());
}

void		tab_up(t_editor *ed, char *line)
{
	//update_winsize(ed);
	increase_tabindex(-1);
	tab_display(ed, line, get_tabinfo());
}

void		tab_right(t_editor *ed, char *line)
{
	//update_winsize(ed);
	increase_tabindex(get_tabinfo()->nb_lines);
	tab_display(ed, line, get_tabinfo());
}

void		tab_left(t_editor *ed, char *line)
{
	//update_winsize(ed);
	increase_tabindex(-get_tabinfo()->nb_lines);
	tab_display(ed, line, get_tabinfo());
}
