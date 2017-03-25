#include "builtins.h"
#include "variable.h"
#include <stdlib.h>
#include "unistd.h"
#include <libft.h>

static char			*get_path(int argc, char **argv)
{
	if (argc == 1)
		return (get_variable("HOME"));
	else
		return (argv[1]);
}

BUILTIN_RET 		builtin_cd(BUILTIN_ARGS)
{
	int		ret;
	char	*new_pwd;

	new_pwd = get_path(argc, argv);
	if (new_pwd != NULL)
	{
		ret = chdir(new_pwd);
		if (ret == 0)
		{
			set_variable("OLDPWD", get_variable("PWD"));
			set_variable("PWD", new_pwd);
			return (STATUS_SUCCESS);
		}
	}
	ft_putendl_fd("42sh: some error with cd", 2);
	return (-1);
}
