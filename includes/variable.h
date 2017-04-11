#ifndef VARIABLE_H
# define VARIABLE_H

# include <stdbool.h>

typedef struct			s_variable
{
	struct s_variable	*next;
	char				*name;
	char				*value;
	bool				exported;
	bool				overwrite;
}						t_variable;

char					*get_variable(char *var);
void					set_variable(char const *var, char const *val);
void					display_variables(bool only_exported);
char					**get_variables_for_execution(t_variable *assignments);

t_variable				*create_variable(char *name, char *value,
											bool exported, bool overwrite);
void					delete_variable(t_variable **var);
void					delete_all_variables(t_variable **var);
t_variable 				*copy_variable(t_variable *e);


#endif
