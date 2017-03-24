#include "parse_input/syntax_tree.h"
#include "errors.h"
#include "utils.h"
#include <libft.h>
#include "execute_syntax_tree.h"

#include <stdio.h>

static void print_ao_sep(t_ao_type sep_type, size_t lvl)
{
	if (sep_type == AO_END)
		return ;
	print_n_char(' ', lvl * 2);
	if (sep_type == AO_AND)
		ft_putstr("&&");
	else if (sep_type == AO_OR)
		ft_putstr("||");
	else
		ft_putstr("BUG");
	ft_putchar('\n');
}

t_error_id	execute_and_or_list(t_and_or_list *ao_list, size_t lvl)
{
	t_error_id		ret;

	if (ao_list == NULL)
		return (NO_ERROR);
	if (ao_list->next == NULL)
		return (execute_pipeline(ao_list->pipeline, lvl));
	print_n_char(' ', (lvl) * 2);
	dprintf(1, "executing and_or_list\n");
	while (ao_list != NULL)
	{
		ret = execute_pipeline(ao_list->pipeline, lvl + 1);
		print_ao_sep(ao_list->separation_type, lvl);
		if ((ret == NO_ERROR && ao_list->separation_type == AO_OR)
			|| (ret != NO_ERROR && ao_list->separation_type == AO_AND))
		{
			print_n_char(' ', (lvl) * 2);
			dprintf(2, "shortcuting and_or_list\n");
			break ;
		}
		ao_list = ao_list->next;
	}
	print_n_char(' ', (lvl) * 2);
	dprintf(2, "done executing and_or_list, %s\n", ret == NO_ERROR ? "ok" : "error");
	return (ret);
}

t_error_id	execute_command_list(t_command_list *cmd_list)
{
	t_error_id		ret;

	dprintf(1, "EXECUTION:\n");
	if (cmd_list == NULL)
		return (NO_ERROR);
	if (cmd_list->next == NULL)
		return (execute_and_or_list(cmd_list->and_or_list, 0));
	dprintf(1, "executing command_list\n");
	while (cmd_list != NULL)
	{
		ret = execute_and_or_list(cmd_list->and_or_list, 1);
		cmd_list = cmd_list->next;
	}
	dprintf(1, "done executing command_list, %s\n", ret == NO_ERROR ? "ok" : "error");
	return (ret);
}
