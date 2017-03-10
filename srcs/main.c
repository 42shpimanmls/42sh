#include <global.h>
#include <init.h>
#include <edit_input.h>

int main(int ac, char **av, char **env)
{
	t_global 	*global;
	char 		*line;

	(void)ac;
	(void)av;
	global = ft_init(env);
	ft_puttab(global->env);

	line = edit_input();
	ft_printf("return edit_input = %s\n", line);

	//CALL BREAK_INPUT(char *line);

	return (EXIT_SUCCESS);
}
