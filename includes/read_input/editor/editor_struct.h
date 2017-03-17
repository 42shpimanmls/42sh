#ifndef EDITOR_STRUCT_H
# define EDITOR_STRUCT_H

#include <stdbool.h>

typedef struct			s_string
{
	struct s_string		*next;
	struct s_string		*prev;  // not link !!!!!!!!!!!!!!!
	char				c;
}						t_string;

typedef struct			s_term
{
	char				*move_left;
	char				*move_right;
	char				*hide_cursor;
	char				*show_cursor;
}						t_term;

typedef struct			s_editor
{
	t_string			*string;
	t_term				*term;
	int					cursor_position;
	bool				need_refresh;
}						t_editor;

#endif
