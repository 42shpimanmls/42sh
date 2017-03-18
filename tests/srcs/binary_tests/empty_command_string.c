#include <CUnit/CUnit.h>
#include <libft.h>
#include <stdlib.h>

static int	call_42sh(char const *args)
{
	char const	*ftsh_path = "../42sh ";
	char		*command;
	int			result;

	command = ft_strjoin(ftsh_path, args);
	result = system(command);
	free(command);
	return (result);
}

void	empty_command_string()
{
	int status = call_42sh("-c \"\"");
	CU_ASSERT(status == EXIT_SUCCESS);
}
