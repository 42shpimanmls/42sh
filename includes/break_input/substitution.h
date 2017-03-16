#ifndef SUBSTITUTION_H
# define SUBSTITUTION_H

# include <stdbool.h>

bool		is_substitution_start(char const *s);
char const	*find_substitution_end(char const *str);

#endif
