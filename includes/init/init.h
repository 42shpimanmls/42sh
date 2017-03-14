#ifndef INIT_H
# define INIT_H

t_variable	*create_variable(char *name, char *value, bool exported);
void		print_variable(t_variable *v);
void		free_variable(t_variable *list);
void		pop_variable_by_name(t_variable **list, char *name);
void		list_push_back(t_variable **list, t_variable *new);

void		parse_options(int argc, char **argv, t_shell_env *shell_env);

#endif
