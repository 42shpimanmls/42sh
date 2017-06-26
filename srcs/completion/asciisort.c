/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asciisort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:09:49 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 15:10:33 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

t_strlis	**getmin(t_strlist **lst)
{
	t_strlist **ret;

	ret = lst;
	while (*lst)
	{
		if (ft_strcmp((*ret)->str, (*lst)->str) > 0)
			ret = lst;
		lst = &(*lst)->next;
	}
	return (ret);
}

void		asciisort(t_strlist **lst)
{
	char		*tmp;
	t_strlist	**min;

	while (*lst)
	{
		min = getmin(lst);
		tmp = (*lst)->str;
		(*lst)->str = (*min)->str;
		(*min)->str = tmp;
		lst = &(*lst)->next;
	}
}
