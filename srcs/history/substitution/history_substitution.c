#include "libft.h"
#include "shell_env.h"
#include "errors.h"

#include "abstract_list.h"
#include "utils.h"
#include "uint.h"

#include "history_substitutions.h"
#include "string_substitution.h"

#include "history/builtin/history.h"

static bool	is_blank_equal_ret(char c)
{
	if (is_posix_blank(c) || c == '\n' || c == '=')
		return (1);
	return (0);
}

static void	check_quotes(char *str, t_uint *i, bool *quoted)
{
	if (str[*i] == '\\')
		*i += 2;
	else if (str[*i] == '\'')
		*quoted = !(*quoted);
}

/*
**	'!' starts a substitution on a history entry
** 	or the line typed so far if the designator is '#'
**	'^' starts a quick substitution (^str1^str2[^])
**	should_run determines if the command is executed or not
**	(it isn't with the p modifier or in case of an error,
**	 but the p modifier still saves it to the history list
**
**	(!% and !* not handled)
*/

static void	choose_and_start_subst(char **str, t_uint *i, int *should_run)
{
	if ((*str)[*i + 1] && (*str)[*i + 1] == '#')
		bang_sharp(str, i, should_run);
	else if (!is_blank_equal_ret((*str)[*i + 1]))
		*should_run = start_substitution(str, i, NULL);
}

int			history_substitution(char **str)
{
	t_uint		i;
	bool		quoted;
	int			should_run;

	i = 0;
	quoted = 0;
	should_run = 1;
	set_error(NO_ERROR);
	while (i < ft_strlen(*str))
	{
		if (get_error() != NO_ERROR)
			return (-1);
		check_quotes(*str, &i, &quoted);
		if (is_bang((*str)[i]) && !quoted)
			choose_and_start_subst(str, &i, &should_run);
		else if (is_circumflex((*str)[i]))
			quick_substitution(str, &i);
		if (i < ft_strlen(*str))
			i++;
	}
	if (!should_run)
		add_to_history_list(&get_shell_env()->history.list, \
							create_history_entry(*str));
	return (should_run);
}
