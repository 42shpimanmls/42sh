#ifndef INIT_H
# define INIT_H

t_variable	*create_variable(char *name, char *value, bool exported);
void		print_variable(t_variable *v);
bool		check_if_variable_exist(t_variable *v, char *name);
void		free_variable(t_variable *list);
void		pop_variable_by_name(t_variable **list, char *name);
void		parse_options(int argc, char **argv, t_shell_env *shell_env);

#endif
