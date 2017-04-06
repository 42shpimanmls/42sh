#include "opt.h"
#include "builtins.h"

/*
** could be use as generic f() for other builtins
** check options presence:
** -e, -E, -s, -n, -esn
*/

int		retrieve_options(int argc, char **argv, t_opt *o)
{
	int	i;
	int	j;

	i = 0;
	o->s = false;
	o->n = false;
	o->e = false;
	while (++i < argc && argv[i][0] == '-' && argv[i][1] != '-')
	{
		j = 0;
		while (argv[i][++j] != '\0')
		{
			if (argv[i][j] == 's')
				o->s = true;
			else if (argv[i][j] == 'n')
				o->n = true;
			else if (argv[i][j] == 'e')
				o->e = true;
		}
	}
	return (i - 1);
}
