#ifndef HISTORY_SUBSTITUTIONS_H
# define HISTORY_SUBSTITUTIONS_H

#include "history.h"

/*
**			history_substitutions.h
*/

int		history_substition(char **str);


/*
**			search_history.h
*/

char	*find_in_history(bool must_start, t_history *history, char *str, t_uint *end);
char	*get_nth_entry(t_history *history, int n);
char	*get_nth_word(char *line, t_uint n);


#endif