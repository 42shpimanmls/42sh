#include "libft.h"
// #include "shell_env.h"
// #include "errors.h"
#include "utils.h"
#include "abstract_list.h"

// #include "history_substitutions.h"
#include "read_input/editor/editor_struct.h" // move struct elsewhere 
#include "read_input/editor/editor.h" // move elsewhere 

void	take_out_backslashes(char **str, char delimiter)
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

char	*get_delimited_str(char *modifier, char delimiter, t_uint *i)
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
	take_out_backslashes(&str, delimiter);
	*i += len;
	return (str);
}