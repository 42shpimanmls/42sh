/*
** generic function to handle conversion of base
** Should works till 999
*/

int		convert_base(int nbr, int base_from, int base_to)
{
	int	ret;

	ret = 0;
	if (nbr >= base_from * base_from)
	{
		ret += base_to * base_to;
		nbr -= base_from * base_from;
	}
	while (nbr >= base_to)
	{
		ret += base_to;
		nbr -= base_from;
	}
	return (ret + nbr);
}
