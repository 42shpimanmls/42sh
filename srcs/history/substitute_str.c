#include "libft.h"
#include "shell_env.h"
#include "errors.h"
#include "utils.h"
#include "abstract_list.h"

#include "history_substitutions.h"
#include "read_input/editor/editor_struct.h" // move struct elsewhere 
#include "read_input/editor/editor.h" // move elsewhere 

/*
	to do: error handling :
 	if not found substitution failed
*/

void		replace_and_repeat(t_str_subst *subst, char **str)
{
	t_uint 		start;

	start = 0;
	if (subst->repeat)
	{
		while (start < ft_strlen(*str))
			start = find_and_replace(str, subst->to_find, subst->replace, start);
	}
	else
		if (find_and_replace(str, subst->to_find, subst->replace, 0) < 0)
			set_error(SUBST_FAIL);
}

t_string	*str_to_list(char *str)
{
	t_string	*l_str;
	t_string	*new;
	int			i;

	i = 0;
	l_str = NULL;
	while (str && str[i])
	{
		new = memalloc_or_die(sizeof(t_string));
		new->c = str[i];
		new->next = NULL;
		list_push_back((t_abstract_list **)&l_str, (t_abstract_list *)new);
		i++;
	}
	return (l_str);
}

static void	take_out_backslashes(char **str, char delimiter)
{
	t_string	*l_str;
	t_string	*tmp;
	size_t		pos;

	if (ft_strchr(*str, '\\'))
	{
		pos = 0;
		l_str = str_to_list(*str);
		tmp = l_str;
		while (l_str)
		{
			if (l_str->c == '\\' && l_str->next && l_str->next->c == delimiter)
				list_pop_at_pos(pos, (t_abstract_list **)&tmp);
			pos++;
			l_str = l_str->next;
		}
		l_str = tmp;
		ft_strdel(str);
		*str = get_string_from_list(l_str);
		free_string(tmp);
	}
}

static char	*get_delimited_str(char *modifier, char delimiter, t_uint *i)
{
	char 	*str;
	char 	*tmp;
	size_t 	len;

	if (!(tmp = ft_strchr(modifier, delimiter)))
	{
		len = ft_strlen(modifier) - 1;
		// -1 because of the \n -> are strings always going to end with \n? does it need to be tested?
		str = ft_strsub(modifier, 0, len);
	}
	else
	{
		len = tmp - modifier;
		while (modifier[len - 1] == '\\')
		{
			tmp = ft_strchr(&modifier[len + 1], delimiter);
			len = tmp - modifier;
		}
		str = ft_strsub(modifier, 0, len);
	}
	ft_putendl(str);
	take_out_backslashes(&str, delimiter);
	ft_putendl(str);
	*i += len;
	return (str);
}

static void	save_substitution(t_str_subst subst)
{
	t_sh_history	*history;

	history = &get_shell_env()->history;
	if (history->last_subst.to_find)
	{
		ft_strdel(&history->last_subst.to_find);
		ft_strdel(&history->last_subst.replace);
	}
	history->last_subst = subst;
}

void		substitute_str(char *modifier, char **str, t_uint *i, bool repeat)
{
	t_str_subst	subst;
	char		delimiter;
	t_error_id	err;

	subst.repeat = repeat;
	delimiter = modifier[(*i)++];
	// // + handle quoted
	if (!(subst.to_find = get_delimited_str(&modifier[*i], delimiter, i)))
		return ;
	(*i)++;
	subst.replace = get_delimited_str(&modifier[*i], delimiter, i);
	if (modifier[*i] == delimiter && modifier[*i - 1] != delimiter)
		(*i)++;
	replace_and_repeat(&subst, str);
	save_substitution(subst);
	if ((err = get_error()) != NO_ERROR)
	{
		modifier = ft_strsub(modifier, 0, *i);
		error_builtin(modifier, NULL, err);
		ft_strdel(&modifier);
	}
}

void		substitute_words_str(char *modifiers, char **str, t_uint *i)
{
	t_token 	*words;
	t_token 	*tmp;

	words = tokenize_for_substitution(*str);
	tmp = words;
	ft_strdel(str);
	while (words)
	{
		substitute_str(modifiers, &words->str, i, false);
		str_join_with_space(str, words->str);
		words = words->next;
	}
	delete_all_tokens(&tmp);
}
