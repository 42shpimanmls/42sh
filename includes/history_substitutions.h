#ifndef HISTORY_SUBSTITUTIONS_H
# define HISTORY_SUBSTITUTIONS_H

#include "history.h"

/*
**			history_substitutions.c
*/

int		history_substition(char **str);


/*
**			get_history_entry.c
*/

char	*find_in_history(bool must_start, t_history *history, char *str, t_uint *end);

/*
**			get_entry_word.c
*/

char	*get_nth_entry(t_history *history, int n);
char	*get_nth_word(char *line, t_uint n);
void	get_entry_word(char **entry, char *str, t_uint *end);
bool	start_word_designator(char c);



#endif