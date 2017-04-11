#ifndef EXEC_H
# define EXEC_H

void	pre_exec(char **cmd);
void	execute(char **cmd, char **env, char **path);
void	exec_if_perm_ok(char *path, char **cmd, char **env);
void	error_message(char *one, char *two, char *three);

#endif
