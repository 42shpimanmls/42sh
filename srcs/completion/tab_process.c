#include <libft.h>
#include "read_input/event_callbacks/event_callback_def.h"
#include "completion.h"

char	*get_cur_word(int curspos, char *line)
{
	int		i;
	char	*ret;

	i = 0;
	while (curspos && line[curspos - 1] != ' ')
	{
		--curspos;
		++i;
	}
	ret = ft_strsub(line, curspos, i);
	return (replace_home(ret));
}

static t_strlist		*get_files(char *path)
{
	char			**split;
	DIR				*dir;
	struct dirent	*dirent;
	t_strlist			*l;

	split = ft_splitfilepath(path);
	if (!(dir = (split[0]) ? opendir(split[0]) : opendir(".")))
	{
		ft_freetabchar(split);
		return (NULL);
	}
	l = NULL;
	while ((dirent = readdir(dir)))
		if (!ft_strncmp(dirent->d_name, split[1], ft_strlen(split[1])))
			add_file(&l, dirent);
	(get_tabinfo()->file_prefix) ? free(get_tabinfo()->file_prefix) : 0;
	get_tabinfo()->file_prefix = str_escape(split[1], " \\;|<>'\"");
	ft_doublearrayndel((void***)&split, 2);
	closedir(dir);
	asciisort(&l);
	return (l);
}

void			choice_tab(t_editor *ed, char *line, char *path)
{
	t_strlist	*l;

	if (ed->last_event == TAB_EVID)
	{
		get_tabinfo()->select_mode = 1;
		tab_display(ed, line, get_tabinfo());
		check_tab_input(ed, line);
		ft_strdel(&path);
		return ;
	}
	clear_tabinfo();
	l = get_files(path);
	if (l)
	{
		get_tabinfo()->list = l;
		get_tabinfo()->total_word = path;
		tab_display(ed, line, get_tabinfo());
		ed->need_refresh = 0;
	}
	else
		ft_strdel(&path);
}
