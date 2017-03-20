#ifndef RANGE_H
#define RANGE_H

#include <stdbool.h>

typedef struct s_range
{
	t_uint	start;
	int		end;
	bool	empty_ok;
}				t_range;

#endif
