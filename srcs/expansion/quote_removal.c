#include "read_input/editor/editor.h"
#include "abstract_list.h"
#include "utils.h"
#include "break_input/quoting.h"

void	print_lstr(t_string *l_str)
{
	while(l_str)
	{
		ft_putchar(l_str->c);
		l_str = l_str->next;
	}
	ft_putchar('\n');
}

/*
**	removes backslash if not quoted
**	or if quoted but quotes a quote
*/

static void	remove_backslash(t_string **l_addr, t_string **l_str, \
								bool *quoted, size_t *pos)
{
	if ((quoted[0] && (*l_str)->next && (*l_str)->next->c == '\'') \
		|| (quoted[1] && (*l_str)->next && (*l_str)->next->c == '\"'))
	{
		*l_str = (*l_str)->next;
		list_pop_at_pos(*pos, (t_abstract_list **)l_addr);
	}
	else if (!quoted[0] && !quoted[1])
	{
		*l_str = (*l_str)->next;
		list_pop_at_pos(*pos, (t_abstract_list **)l_addr);
		(*pos)--;
	}
}

/*
**	removes single or double quote if unquoted
*/

static void	remove_quote(t_string **l_addr, bool *quoted, size_t *pos, char c)
{
	size_t			i;
	char const		*quotes;

	quotes = "\'\"";
	i = ft_strchr(quotes, c) - quotes;
	if (!quoted[!i])
	{
		list_pop_at_pos(*pos, (t_abstract_list **)l_addr);
		(*pos)--;
		quoted[i] = !quoted[i];
	}
}

static void	remove_quotes(t_string **l_addr)
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
				remove_backslash(l_addr, &l_str, quoted, &pos);
			else
				remove_quote(l_addr, quoted, &pos, l_str->c);
		}
		pos++;
		l_str = l_str->next;
	}
}

char	*quote_removal(char *str)
{
	t_string		*l_str;
	char	*result;

	l_str = str_to_list(str);
	remove_quotes(&l_str);
	result = get_string_from_list(l_str);
	ft_printf("after quote removal: %s\n", result);
	free_string(l_str);
	return (result);
}
