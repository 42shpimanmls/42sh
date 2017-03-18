#include "shell_env.h"
#include "parse_syntax_tree.h"
#include "print_syntax_tree.h"
#include "ftsh.h"

void			parse_input(void)
{
	t_shell_env	*sh_env;

	sh_env = get_shell_env();
	sh_env->syntax_tree = parse_command_list(sh_env->tokens);
#ifdef FTSH_DEBUG
	ft_putendl("<syntax_tree>");
	print_command_list(sh_env->syntax_tree, 0);
	ft_putendl("</syntax_tree>");
#endif
}
