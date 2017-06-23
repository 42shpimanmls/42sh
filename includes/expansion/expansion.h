#ifndef EXPANSION_H
# define EXPANSION_H

# include "strlist.h"
# include "variable.h"

# define IS_QU_SIMPLE 0b0001
# define IS_QU_DOUBLE 0b0010

void				expand_cmd_words(char ***words_addr);
char				*command_substition(char const *word);
t_strlist			*field_splitting(char const *word);
char				*parameter_expansion(char const *word);
void				quote_removal(char **word);
void				handle_quotes(char c, char *quoted);
char				*tilde_expansion(char const *word);
t_strlist			*split_subsitutions(char const *word);
t_strlist			*split_subsitutions_run(char const *word,
					char const *passv_str_start,
					t_strlist *result, char quoted);
void				expand_assignments_values(t_variable *assignments);

#endif
