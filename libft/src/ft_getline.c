/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 12:07:13 by pilespin          #+#    #+#             */
/*   Updated: 2016/02/29 18:19:45 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_parse(char **stk, char *tmp, int fd)
{
	int	i;

	if (ft_strchr(tmp, '\n'))
	{
		i = -1;
		while (tmp[++i])
		{
			if (tmp[i] == '\n')
			{
				stk[fd] = ft_strsub(tmp, i + 1, ft_strlen(tmp) - i - 1);
				return (ft_strsub(tmp, 0, i));
			}
		}
	}
	return (NULL);
}

char		*ft_get_old_data(char **stk, int fd)
{
	if (ft_strlen(stk[fd]) > 0)
		return (stk[fd]);
	return (ft_strnew(1));
}

char		*ft_getline(int const fd)
{
	char		*tmp;
	char		*tmp2;
	char		*buff;
	int			ret;
	static char	*stk[500];

	if (fd < 0)
		return (NULL);
	tmp = ft_get_old_data(stk, fd);
	tmp2 = ft_parse(stk, tmp, fd);
	if (!tmp2)
	{
		buff = (char *)malloc(BUFF_SIZE + 1);
		while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
		{
			buff[ret] = '\0';
			tmp = ft_strjoinf(tmp, buff, 1);
			tmp2 = ft_parse(stk, tmp, fd);
			break ;
		}
		free(buff);
	}
	free(tmp);
	return (tmp2);
}
