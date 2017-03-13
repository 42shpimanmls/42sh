/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 12:07:13 by pilespin          #+#    #+#             */
/*   Updated: 2016/02/29 18:19:58 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_keep_just_line(char *tmp)
{
	char *tmp2;

	tmp2 = ft_strchr(tmp, '\n');
	tmp[ft_strlen(tmp) - ft_strlen(tmp2)] = '\0';
	return (ft_strdup(tmp2 + 1));
}

static int	ft_suit(int fd, char *tmp, char **tmp3, char **line)
{
	int		ret;
	char	*buff;

	ret = 1;
	if (ft_strchr(tmp, '\n'))
		tmp3[fd] = ft_keep_just_line(tmp);
	else
	{
		buff = (char *)malloc(BUFF_SIZE + 1);
		while (ret > 0)
		{
			ret = read(fd, buff, BUFF_SIZE);
			buff[ret] = '\0';
			tmp = ft_strjoinf(tmp, buff, 1);
			if (ft_strchr(buff, '\n'))
			{
				tmp3[fd] = ft_keep_just_line(tmp);
				ft_strdel(&buff);
				break ;
			}
		}
	}
	*line = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (ret);
}

int			ft_get_next_line(int const fd, char **line)
{
	int			ritourn;
	char		*tmp;
	static char	*tmp3[256];

	if (fd < 0 || (line == NULL))
		return (-1);
	if (tmp3[fd])
		tmp = ft_strdup(tmp3[fd]);
	else
		tmp = ft_strnew(0);
	ritourn = ft_suit(fd, tmp, tmp3, line);
	if (ritourn == -1)
		return (-1);
	return ((ritourn == 0) ? 0 : 1);
}
