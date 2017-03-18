#include <libft.h>
#include "tokenizer.h"
#include "shell_env.h"


// DANGER
/*#include <stdio.h>

void	test_super_split(t_token const *tokens)
{
	t_token		**split;
	size_t		split_len;
	size_t		u;
	t_token_id	and_or[2];

	ft_putendl("split and_or");
	and_or[0] = AND_IF_TOKID;
	and_or[1] = OR_IF_TOKID;
	split = split_tokens_mult(tokens, and_or, 2, &split_len);
	u = 0;
	while (u < split_len)
	{
	printf("Slice %lu:\n", u);
		print_tokens(split[u]);
		u += 1;
	}
}

void	test_split(t_token const *tokens)
{
	t_token		**split;
	size_t		split_len;
	size_t		u;

	ft_putendl("split list");
	split = split_tokens_at(tokens, SEMI_TOKID, &split_len);
	u = 0;
	while (u < split_len)
	{
	printf("Slice %lu:\n", u);
		print_tokens(split[u]);
		u += 1;
	}
}*/

void	break_input(void)
{
	t_shell_env *shell_env;

	shell_env = get_shell_env();
	shell_env->tokens = tokenize(shell_env->input_string);
#ifdef FTSH_DEBUG
	ft_putendl("<tokens>");
	print_tokens(shell_env->tokens);
	ft_putendl("</tokens>");
#endif
	/*test_split(shell_env->tokens);
	test_super_split(shell_env->tokens);*/
}
