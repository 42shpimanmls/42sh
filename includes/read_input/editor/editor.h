#ifndef EDITOR_H
# define EDITOR_H

# include "read_input/editor/editor_struct.h"

t_editor	*init_editor();
void		print_string(t_string *s);
t_editor 	*get_editor();
void		add_to_string(t_editor *ed, char c);
char		*get_string_from_list(t_string *s);
void		free_string(t_string *s);
void		ft_clear_line(t_string *s);

#endif
