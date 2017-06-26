#include "token.h"
#include <libft.h>
#include "utils.h"

void	print_token(t_token const *token)
{
	ft_printf("%s: s=", token->type->name);
	ft_putchar('\n');
}

void	print_tokens(t_token const *tokens)
{
	if (tokens == NULL)
		return ;
	print_token(tokens);
	print_tokens(tokens->next);
}
