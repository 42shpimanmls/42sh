#ifndef EXPANSION_H
# define EXPANSION_H

#include "strlist.h"

// #define EXPANSION_DEBUG

#define IS_QU_SIMPLE 0b0001
#define	IS_QU_DOUBLE 0b0010

void				expand_cmd_words(char ***words_addr);
t_strlist			*command_substition(char const *word);
void				field_splitting(t_strlist **l_addr);
void				quote_removal(char **word);

#endif
