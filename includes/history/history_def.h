#ifndef HISTORY_DEF_H
#define HISTORY_DEF_H

#include "file_positions.h"

/*
	exported env var in shells / + need absolute path
*/
# define HISTFILE ".42sh_history"

typedef struct 	s_str_subst {

	char 	*to_find;
	char	*replace;
	bool	repeat;
	bool	repeat_word;

}				t_str_subst;

typedef struct			s_history
{
	struct s_history	*next;
	char				*line;
	bool				appended;
	struct s_history	*prev;
}						t_history;

typedef struct 			s_sh_history
{
	// size_t				size;
	t_history			*history_list;
	t_file_position		*history_files;
	t_str_subst			*last_subst;
	char				*last_search;
}						t_sh_history;

#endif
