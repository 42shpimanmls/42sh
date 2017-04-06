#include "builtins.h"
#include "opt.h"
#include "libft.h"

/*
** for every arguments:
** '-e': backslash escapes interpretation
** handle '-n' options
** '-s' option: do not display space for last str
*/

int		builtin_echo(int argc, char **argv)
{
	int		i;
	t_opt	*o;

	o = (t_opt*)malloc(sizeof(t_opt));
	i = retrieve_options(argc, argv, o, "sne");
	while (++i < argc)
	{
		if (o->e == true)
		{
			if (escape_char(argv[i]) == true)
				break ;
		}
		else
			ft_putstr(argv[i]);
		if (o->s == false && i + 1 < argc)
			ft_putchar(' ');
	}
	if (o->n == false)
		ft_putchar('\n');
	free(o);
	return (STATUS_SUCCESS);
}

/*
** Parcour every char
** if start with '\':
** if '\c' stop displaying
** display one char '\x' for two chars "\x"
** increment index to not display escaped chars
*/

bool	escape_char(char *str)
{
	int	i;
	int	oct;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '\\' && str[i + 1])
		{
			if (str[i + 1] == 'c')
				return (true);
			if (escape(*(&str[i + 1])) == true)
				i += 1;
			else if (str[i + 1] == '0' && (oct = octal(&str[i + 1])) > 0)
				i += 1 + oct;
			else
				ft_putchar(str[i]);
		}
		else
			ft_putchar(str[i]);
	}
	return (false);
}

/*
** return status if found char
*/

bool	escape(int c)
{
	if (c == '\\')
		ft_putchar('\\');
	else if (c == 'a')
		ft_putchar('\a');
	else if (c == 'b')
		ft_putchar('\b');
	else if (c == 'e')
		ft_putchar('\e');
	else if (c == 'f')
		ft_putchar('\f');
	else if (c == 'n')
		ft_putchar('\n');
	else if (c == 'r')
		ft_putchar('\r');
	else if (c == 't')
		ft_putchar('\t');
	else if (c == 'v')
		ft_putchar('\v');
	else
		return (false);
	return (true);
}

/*
** Check good format for octal: '\0NNN':
** [0-8], [0-8][0-8], [0-1][0-8][0-8]
** prevent segfault
** if not good format for three char: return
** substitute str, convert to int, convert to base 8 and print
** return number of char to not display
*/

int		octal(char *c)
{
	int		n;
	char	*str;
	int		nbr;
	int		len;

	n = 0;
	len = ft_strlen(c);
	if (3 < len && is_octal(c[3]) == true)
		n += 1;
	if (2 < len && is_octal(c[2]) == true)
		n += 1;
	if (1 < len && ((n == 2 && (c[1] == '0' || c[1] == '1')) ||
		(n < 2 && is_octal(c[1]) == true)))
		n += 1;
	if (n == 0)
		return (0);
	str = ft_strsub(c, 1, n);
	nbr = ft_atoi(str);
	ft_strdel(&str);
	ft_putchar((char)convert_base(nbr, 10, 8));
	return (n);
}

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
