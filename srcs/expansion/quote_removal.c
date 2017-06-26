/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:09:36 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 17:22:15 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_input/editor/editor.h"
#include "abstract_list.h"
#include "utils.h"
#include "break_input/quoting.h"
#include "expansion.h"

static t_string		*remove_backslash(t_string **l_addr, t_string **l_str, \
								bool *quoted, size_t *pos)
{
	void	*to_del;

	if (!quoted[0] && (quoted[1] && (*l_str)->next && \
		((*l_str)->next->c == '\"' || (*l_str)->next->c == '\\')))
	{
		*l_str = (*l_str)->next;
		to_del = list_pop_at_pos(*pos, (t_abstract_list **)l_addr);
		*l_str = ((t_string *)to_del)->next;
		free(to_del);
		(*pos)--;
	}
	else if (!quoted[0] && !quoted[1])
	{
		to_del = list_pop_at_pos(*pos, (t_abstract_list **)l_addr);
		*l_str = ((t_string *)to_del)->next;
		free(to_del);
		(*pos)--;
	}
	if ((*l_str) && is_quote((*l_str)->c))
	{
		(*l_str) = (*l_str)->next;
		(*pos)++;
	}
	return (*l_str);
}

static t_string		*remove_quote(t_string **l_addr, t_string *l_str, \
						bool *quoted, size_t *pos)
{
	size_t			i;
	char const		*quotes;
	void			*to_del;
	t_string		*ret;

	quotes = "\'\"";
	i = ft_strchr(quotes, l_str->c) - quotes;
	if (!quoted[!i])
	{
		to_del = list_pop_at_pos(*pos, (t_abstract_list **)l_addr);
		ret = ((t_string *)to_del)->next;
		free(to_del);
		(*pos)--;
		quoted[i] = !quoted[i];
		return (ret);
	}
	return (l_str);
}

static void			remove_quotes(t_string **l_addr)
{
	bool			quoted[2];
	size_t			pos;
	t_string		*l_str;

	ft_bzero(quoted, sizeof(bool) * 2);
	l_str = *l_addr;
	pos = 0;
	while (l_str)
	{
		if (is_quote(l_str->c))
		{
			if (l_str->c == '\\')
				l_str = remove_backslash(l_addr, &l_str, quoted, &pos);
			else
				l_str = remove_quote(l_addr, l_str, quoted, &pos);
		}
		else
			l_str = l_str->next;
		pos++;
	}
}

static bool			has_quotes(char *str)
{
	while (*str)
	{
		if (is_quote(*str))
			return (true);
		str++;
	}
	return (false);
}

void				quote_removal(char **word)
{
	t_string		*l_str;

	if (has_quotes(*word))
	{
		l_str = str_to_list(*word);
		remove_quotes(&l_str);
		ft_strdel(word);
		*word = get_string_from_list(l_str);
		free_string(l_str);
	}
}
