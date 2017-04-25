#include "utils.h"
#include "range.h"

#include "history_substitutions.h"

static void	set_each_range(char *str, t_range *range, int *i, bool start)
{
	if (start)
		range->start = ft_atoi(&str[*i]);
	else
		range->end = ft_atoi(&str[*i]);
	*i += number_len(&str[*i]);
}

static void	parse_end(char *str, int *i, t_range *range)
{
	if (ft_isdigit(str[(*i) + 1]))
	{
		(*i)++;
		set_each_range(str, range, i, false);
	}
	else
		range->end = -2;
}

/*
**	‘-y’ abbreviates ‘0-y’
**	'x-$' = x-last
**	x- is x-$ but omits the last word
**	x*  = x-$
*/

int			parse_range(char *str, int *i, t_range *range)
{
	if (str[*i] == '-')
		parse_end(str, i, range);
	else
	{
		set_each_range(str, range, i, true);
		if (str[*i] && str[*i] == '-')
		{
			(*i)++;
			if (str[*i] && ft_isdigit(str[*i]))
				set_each_range(str, range, i, false);
			else if (str[*i] && str[*i] == '$')
			{
				(*i)++;
				range->end = -1;
			}
			else
				range->end = -2;
		}
		else if (str[*i] == '*')
		{
			(*i)++;
			range->end = -2;
		}
	}
	return (0);
}
