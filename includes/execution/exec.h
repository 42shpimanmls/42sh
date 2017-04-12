#ifndef EXEC_H
# define EXEC_H

void	pre_exec(t_simple_command *cmd);
void	execute(char **cmd, char **env, char **path);
void	exec_if_perm_ok(char *path, char **cmd, char **env);
void	error_message(char *one, char *two, int ret);

#endif
