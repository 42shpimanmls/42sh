#include "libft.h"
#include "shell_env.h"
#include "env_tools.h"
#include "exec.h"
#include <unistd.h>

/*
** Retrieve env vars and PATH
*/

void	pre_exec(char **cmd)
{
	char	**path;
	char	**env;
 
	env = tabify(get_shell_env()->variables);
	path = ft_strsplit(get_tenv(env, "PATH"), ':');
	execute(cmd, env, path);
	ft_freetabchar(path);
	ft_freetabchar(env);
}

/*
** If local executable:
** Check file exist.
** Check user have executable rights on it.
** Execute it and exit fork.
** Else: execute path
** exit the fork if the no execution because execution stop the fork
*/

void	execute(char **cmd, char **env, char **path)
{
	if (cmd[0][0] == '.' && cmd[0][1] == '/' && cmd[0][2] != '\0')
	{
		cmd[0] = &cmd[0][2];
		if (access(cmd[0], F_OK) == -1)
			error_message(cmd[0], "no such executable", "exit");
		else if (access(cmd[0], X_OK) == -1)
			error_message(cmd[0], "no rights to execute it", "exit");
		else
			execve(cmd[0], &cmd[0], env);
	}
	else
		execute_path(cmd, env, path);
	error_message(cmd[0], "no such command", "exit");
}

/*
** Search for executable in PATH paths.
** then run it.
** Execute direct given path like /bin/ls
*/

void	execute_path(char **cmd, char **env, char **path)
{
	int	i;
	char	*p_exec;

	i = -1;
	if (path != NULL)
		while (path[++i] != NULL)
		{
			p_exec = ft_strjoinf(path[i], ft_strjoin("/", cmd[0]), 2);
			exec_if_perm_ok(p_exec, cmd, env);
			ft_strdel(&p_exec);
		}
	exec_if_perm_ok(cmd[0], cmd, env);
}

/*
** Check permissions and executions rights on the file.
** If it's ok, execute it.
** Else: error message
*/

void	exec_if_perm_ok(char *path, char **cmd, char **env)
{
	if (access(path, F_OK) != -1)
	{
		if (access(path, X_OK) != -1)
			execve(path, &cmd[0], env);
		else
			error_message(path, "no rights to execute it", "exit");
	}
}

void    error_message(char *one, char *two, char *three)
{
	if (three == NULL || ft_strcmp(three, "exit") == 0)
	{
		ft_dprintf(2, ">42sh: %s: %s.\n", one, two);
		if (three != NULL && ft_strcmp(three, "exit") == 0)
			exit(0);
	}
	else
		ft_dprintf(2, ">42sh: %s: %s: %s.\n", one, two, three);
}
