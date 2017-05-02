#include <stdio.h>
#include <limits.h>

int	main(void)
{
	int i;

	i = 0;
	while (i++ < PATH_MAX)
		putchar('a');
	putchar('\n');
	i = 0;
	while (i++ < PATH_MAX - 1)
		putchar('b');
	putchar('\n');
	return (0);
}
