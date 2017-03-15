#include <libft.h>
#include "tokenizer/token.h"
#include "shell_env.h"

void break_input(void)
{
	t_shell_env *shell_env;

	shell_env = get_shell_env();
	shell_env->tokens = tokenize(shell_env->input_string);
	ft_putendl("<tokens>");
	print_tokens(shell_env->tokens);
	ft_putendl("</tokens>");
}
