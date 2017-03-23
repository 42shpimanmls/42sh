# include <libft.h>
# include <term.h>
# include <termios.h>
# include <curses.h>

# include "utils.h"
# include "abstract_list.h"
# include "shell_env.h"

# include "read_input/editor/editor.h"
# include "read_input/event_callbacks/event_callback_def.h"
# include "read_input/termcap/init_deinit.h"

#include "history.h"

#include "variable.h"

typedef struct		s_unmatched_def
{
	t_error_id	id;
	char const	*str;
}					t_unmatched_def;

static char const	*get_unmatched_str(t_error_id id)
{
	static t_unmatched_def	const	defs[] = {
		{ UNMATCHED_SINGLE_QUOTE, "quote" },
		{ UNMATCHED_DOUBLE_QUOTE, "dquote" },
		{ UNMATCHED_BACKQUOTE, "bquote" },
		{ UNEXPECTED_IF, "cmdif" },
		{ UNEXPECTED_PIPE, "pipe" },
	};
	size_t							u;

	u = 0;
	while (u < 6)
	{
		if (defs[u].id == id)
			return (defs[u].str);
		u++;
	}
	return ("unknown");
}

char				*gen_prompt(void)
{
	char		*result;
	char		*tmp;
	t_shell_env	*shell_env;

	shell_env = get_shell_env();
	if (!shell_env->last_unmatched)
	{
		tmp = ft_strjoinf(get_variable("PWD"), "]$ ", 1);
		result = ft_strjoin("[", tmp);
		free(tmp);
	}
	else
	 	result = ft_strjoin(get_unmatched_str(shell_env->last_unmatched), "> ");

	return (result);
}
