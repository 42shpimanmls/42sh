#include "libft.h"
#include "shell_env.h"
#include "exec.h"
#include <unistd.h>
#include <paths.h>

/*
** Retrieve env vars and PATH
*/

void	pre_exec(char **cmd)
{
	char	*spath;
	char	**path;
	char	**env;
 
	env = get_variables_for_execution(get_shell_env()->variables);
	if ((spath = get_variable("PATH")) == NULL)
		spath = ft_strdup(_PATH_DEFPATH);
	path = ft_strsplit(spath, ':');
	ft_strdel(&spath);
	execute(cmd, env, path);
	ft_freetabchar(path);
	ft_freetabchar(env);
}

/*
** Search for executable in PATH paths.
** if found, execute it.
** else if contains '/':
** Execute direct given path like '/bin/ls' or './42sh'
** exit the fork if the no execution because execution stop the fork
** if found nothing: trow a message
*/

void	execute(char **cmd, char **env, char **path)
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
	if (ft_strchr(cmd[0], '/') != NULL)
		exec_if_perm_ok(cmd[0], cmd, env);
	error_message(cmd[0], "no such command", "exit");
}

/*
** Check file exist.
** Check permissions and executions rights on the file.
** If it's ok, execute it.
** Execute it and exit fork.
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
		ft_dprintf(2, ">%s: %s: %s.\n", SHNAME, one, two);
		if (three != NULL && ft_strcmp(three, "exit") == 0)
			exit(0);
	}
	else
		ft_dprintf(2, ">%s: %s: %s: %s.\n", SHNAME, one, two, three);
}
