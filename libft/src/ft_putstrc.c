/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 12:43:16 by pilespin          #+#    #+#             */
/*   Updated: 2015/10/15 15:30:17 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrc(int color, int background, char *str)
{
	if (color >= 0 && color <= 7)
	{
		ft_putstr("\033[");
		ft_putnbr(color + 30);
		if (background >= 0 && background <= 7)
		{
			ft_putstr(";");
			ft_putnbr(background + 40);
		}
		ft_putstr("m");
		ft_putstr(str);
		ft_putstr("\033[0m");
	}
}

/*
**	0 : noir ;
**	1 : rouge ;
**	2 : vert ;
**	3 : jaune ;
**	4 : bleu ;
**	5 : rose ;
**	6 : cyan ;
** 	7 : gris.
*/
