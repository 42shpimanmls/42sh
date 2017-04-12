# include "libft.h"

char	*get_options_core(int ac, char **av)
{
	char	*arg;
	int		i;
	int		j;

	if (ac <= 1 || !av || ft_tablen(av) <= 1)
		return (NULL);
	arg = NULL;
	i = 0;
	while (++i < ac && av[i])
	{
		if (ft_strlen(av[i]) >= 2 && av[i][0] == '-')
		{
			j = 0;
			while (av[i][++j])
			{
				if (ft_isalpha(av[i][j]))
				{
					if (!ft_strchr(arg, av[i][j]))
						arg = ft_strjoinf(arg, ft_strndup(&av[i][j], 1), 3);
				}
			}
		}
	}
	return (arg);
}
