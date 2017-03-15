#ifndef INIT_H
# define INIT_H

void		init(char **env);
t_variable	*create_variable(char *name, char *value, bool exported);
void		print_variable(t_variable *v);
void		free_variable(t_variable *list);
void		pop_variable_by_name(t_variable **list, char *name);

#endif
