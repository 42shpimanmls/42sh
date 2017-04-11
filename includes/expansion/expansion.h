#ifndef EXPANSION_H
# define EXPANSION_H

#include "strlist.h"

void				expand_cmd_words(char ***words_addr);
char				*command_substition(char const *word);
t_strlist			*field_splitting(char const *word);
char				*quote_removal(char *str);

#endif
