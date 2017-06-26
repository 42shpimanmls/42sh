#include "parse_input/syntax_tree.h"
#include "errors.h"
#include "utils.h"
#include <libft.h>
#include "execute_syntax_tree.h"

#include <stdio.h>

static void	print_ao_sep(t_ao_type sep_type, size_t lvl)
{
#ifdef FTSH_DEBUG
	if (sep_type == AO_END)
		return ;
	print_n_char_fd(' ', lvl * 2, 2);
	if (sep_type == AO_AND)
		ft_putstr_fd("&&", 2);
	else if (sep_type == AO_OR)
		ft_putstr_fd("||", 2);
	else
		ft_putstr_fd("BUG", 2);
	ft_putchar_fd('\n', 2);
#else
	(void)sep_type;
	(void)lvl;
#endif
}

t_error_id	execute_and_or_list(t_and_or_list *ao_list, size_t lvl)
{
	t_error_id		ret;
	bool			skip;

	if (ao_list == NULL)
		return (NO_ERROR);
	if (ao_list->next == NULL)
		return (execute_pipeline(ao_list->pipeline, lvl));
#ifdef FTSH_DEBUG
	print_n_char_fd(' ', (lvl) * 2, 2);
	dprintf(2, "executing and_or_list\n");
#endif
	skip = false;
	while (ao_list != NULL)
	{
		if (!skip)
		{
			execute_pipeline(ao_list->pipeline, lvl + 1);
			ret = get_last_exit_status();
			print_ao_sep(ao_list->separation_type, lvl);
		}
		skip = false;
		if ((ret == NO_ERROR && ao_list->separation_type == AO_OR)
			|| (ret != NO_ERROR && ao_list->separation_type == AO_AND))
		{
#ifdef FTSH_DEBUG
			print_n_char_fd(' ', (lvl) * 2, 2);
			dprintf(2, "shortcuting and_or_list\n");
#endif
			skip = true;
		}
		ao_list = ao_list->next;
	}
#ifdef FTSH_DEBUG
	print_n_char_fd(' ', (lvl) * 2, 2);
	dprintf(2, "done executing and_or_list, %s\n", ret == NO_ERROR ? "ok" : "error");
#endif
	return (ret);
}

t_error_id	execute_command_list(t_command_list *cmd_list)
{
	t_error_id		ret;
#ifdef FTSH_DEBUG
	dprintf(2, "EXECUTION:\n");
#endif
	if (cmd_list == NULL)
		return (NO_ERROR);
	if (cmd_list->next == NULL)
		return (execute_and_or_list(cmd_list->and_or_list, 0));
#ifdef FTSH_DEBUG
	dprintf(2, "executing command_list\n");
#endif
	while (cmd_list != NULL)
	{
		ret = execute_and_or_list(cmd_list->and_or_list, 1);
		cmd_list = cmd_list->next;
	}
#ifdef FTSH_DEBUG
	dprintf(2, "done executing command_list, %s\n", ret == NO_ERROR ? "ok" : "error");
#endif
	return (ret);
}
