/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_on_tty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 16:28:06 by asenat            #+#    #+#             */
/*   Updated: 2017/06/22 16:36:57 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_env.h"
#include <libft.h>

void	putchar_on_tty(const char c)
{
	ft_putchar_fd(c, get_shell_env());
}

void	putstr_on_tty(const char *str)
{
	ft_putstr_fd(c, get_shell_env());
}

void	putchar_on_tty(const char *str)
{
	ft_putendl_fd(c, get_shell_env());
}
