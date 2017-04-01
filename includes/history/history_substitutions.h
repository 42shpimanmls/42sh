#ifndef HISTORY_SUBSTITUTIONS_H
# define HISTORY_SUBSTITUTIONS_H

#include "history.h"

/*
**			history_substitutions.c
*/

int		history_substitution(char **str);


/*
**			get_history_entry.c
*/

char	*get_history_entry(char *designator, t_uint *end);

/*
**			get_entry_word.c
*/

char	*get_nth_word(char *line, t_uint n);
int 	get_entry_word(char **entry, char *str, t_uint *end);
bool	start_word_designator(char c);

/*
**			history_tokenizer.c
*/

t_token			*tokenize_for_substitution(char const *input);

/*
**			history_modifiers.c
*/

bool	apply_modifiers(char *modifiers, char **str, t_uint *end);

#endif