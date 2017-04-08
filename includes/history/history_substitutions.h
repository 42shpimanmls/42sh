#ifndef HISTORY_SUBSTITUTIONS_H
# define HISTORY_SUBSTITUTIONS_H

#include "history.h"
#include "range.h"

/*
**			history_substitutions.c
*/

int				history_substitution(char **str);

/*
**			get_history_entry.c
*/

char			*get_history_entry(char *designator, t_uint *end);
char			*get_nth_entry(t_history *history, int n);

/*
**			get_entry_word.c
*/

char			*get_nth_word(char *line, t_uint n);
void 			get_entry_word(char **entry, char *str, t_uint *end);


/*
**			word_range.c
*/

int 			parse_range(char *str, int *i, t_range *range);
void 			range_selection(char *str, int *i, t_range *range, char **words);
char			*get_word_range(char *line, t_range *range);

/*
**			word_designators.c
*/

bool			start_word_designator(char c);
void			parse_word_designators(char *str, int *i, char **words, t_range *range, char **entry);

/*
**			history_tokenizer.c
*/

t_token			*tokenize_for_substitution(char const *input);

/*
**			history_modifiers.c
*/

bool			apply_modifiers(char *modifiers, char **str, t_uint *end);

/*
**			substitute_str.c
*/

void			substitute_str(char *modifier, char **str, t_uint *i, bool repeat);
void			substitute_words_str(char *modifiers, char **str, t_uint *i);
void			replace_and_repeat(t_str_subst *subst, char **str);

/*
**			perform_hist_subst
*/

int				quick_substitution(char **str, t_uint *i);
void 			perform_substitution(char **str, char *hist_entry, \
										t_uint *start, t_uint end);

#endif
