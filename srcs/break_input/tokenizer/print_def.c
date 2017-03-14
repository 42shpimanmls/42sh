#include "token_def.h"
#include "uint.h"

// REMPLACER LES PRINTFS ET PUTCHAR!!
#include <stdio.h>

static void					print_token_str(char const *str)
{
	char c;

	printf(": ");
	if (str == NULL)
	{
		printf("not an operator");
		return ;
	}
	putchar('"');
	while ((c = *str) != '\0')
	{
		if (c == '\n')
			printf("\\n");
		else
			putchar(c);
		str += 1;
	}
	putchar('"');
}

void						print_token_def(t_token_def const *def)
{
	printf("%s", def->name);
	print_token_str(def->str);
}

void						print_token_defs(void)
{
	t_token_def const	*defs;
	t_uint				u;

	printf("TOKEN DEFS:\n");
	defs = get_token_defs();
	u = 0;
	while (u < TOKEN_DEF_COUNT)
	{
		print_token_def(defs + u);
		putchar('\n');
		u += 1;
	}
}
