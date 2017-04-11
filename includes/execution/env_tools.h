#ifndef ENV_TOOLS_H
# define ENV_TOOLS_H

char	**tabify(t_variable *env);
int	lstsize(t_variable *env);
char	*get_tenv(char **env, char *var);

#endif
