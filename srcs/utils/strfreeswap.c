#include <stdlib.h>

void	strfreeswap(char **dst_addr, char *src)
{
	free(*dst_addr);
	*dst_addr = src;
}
