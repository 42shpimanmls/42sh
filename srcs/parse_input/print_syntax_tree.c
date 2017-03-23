#include "syntax_tree.h"
#include "utils.h"
#include <libft.h>

static void print_assignments(t_variable const *a, size_t lvl)
{
	if (a == NULL)
		return ;
	print_n_char(' ', (lvl) * 2);
	ft_putstr("assignment(s):");
	while (a != NULL)
	{
		ft_putchar(' ');
		ft_putstr(a->name);
		ft_putchar('=');
		ft_putstr(a->value);
		if (a->next != NULL)
			ft_putstr(",");
		a = a->next;
	}
	ft_putchar('\n');
}

static int 	get_default_fd(t_redir_type type)
{
	if (type == REDIR_OUTPUT || type == APPEND_OUTPUT)
		return (1);
	else if (type == REDIR_INPUT)
		return (0);
	return (-1);
}

static void print_redirections(t_redirection const *r, size_t lvl)
{
	if (r == NULL)
		return ;
	print_n_char(' ', (lvl) * 2);
	ft_putstr("redirection(s):");
	while (r != NULL)
	{
		ft_putchar(' ');
		if (r->n >= 0)
			ft_putnbr(r->n);
		else
			ft_putnbr(get_default_fd(r->type));
		ft_putchar(' ');
		ft_putstr(get_token_def((t_token_id)r->type)->str);
		ft_putchar(' ');
		ft_putstr(r->word);
		if (r->next != NULL)
			ft_putstr(",");
		r = r->next;
	}
	ft_putchar('\n');
}

static void print_simple_command(t_simple_command const *cmd, size_t lvl)
{
	char **it;

	if (cmd->argv[0] != NULL)
	{
		print_n_char(' ', (lvl) * 2);
		ft_putstr("command: ");
		ft_putendl(*cmd->argv);
		if (cmd->argv[1] != NULL)
		{
			print_n_char(' ', (lvl) * 2);
			ft_putstr("argument(s): ");
			it = cmd->argv + 1;
			while ((*it) != NULL)
			{
				if (it != cmd->argv + 1)
					ft_putchar(' ');
				print_non_ascii_str(*it);
				it++;
			}
			ft_putchar('\n');
		}
	}
	print_assignments(cmd->assignments, lvl);
	print_redirections(cmd->redirections, lvl);
}

static void print_pipeline(t_simple_command const *pip, size_t lvl)
{
	if (pip == NULL)
	{
		print_n_char(' ', lvl * 2);
		ft_putendl("empty");
		return ;
	}
	if (pip->next == NULL)
	{
		print_simple_command(pip, lvl);
		return ;
	}
	print_n_char(' ', lvl * 2);
	ft_putendl("pipeline:");
	while (pip != NULL)
	{
		print_simple_command(pip, lvl + 1);
		pip = pip->next;
		if (pip != NULL)
		{
			print_n_char(' ', lvl * 2);
			ft_putchar('|');
			ft_putchar('\n');
		}
	}
}

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

static void	print_and_or_list(t_and_or_list const *ao_list, size_t lvl)
{
	if (ao_list == NULL)
	{
		print_n_char(' ', lvl * 2);
		ft_putendl("empty");
		return ;
	}
	if (ao_list->next == NULL)
	{
		print_pipeline(ao_list->pipeline, lvl);
		return ;
	}
	print_n_char(' ', lvl * 2);
	ft_putendl("and_or_list:");
	while (ao_list != NULL)
	{
		print_pipeline(ao_list->pipeline, lvl + 1);
		if (ao_list->next != NULL)
			print_ao_sep(ao_list->separation_type, lvl);
		ao_list = ao_list->next;
	}
}

void	print_command_list(t_command_list const *cmd_list, size_t lvl)
{
	if (cmd_list == NULL)
	{
		print_n_char(' ', lvl * 2);
		ft_putendl("empty");
		return ;
	}
	if (cmd_list->next == NULL)
	{
		print_and_or_list(cmd_list->and_or_list, lvl);
		return ;
	}
	print_n_char(' ', lvl * 2);
	ft_putendl("command_list:");
	while (cmd_list != NULL)
	{
		print_and_or_list(cmd_list->and_or_list, lvl + 1);
		cmd_list = cmd_list->next;
		if (cmd_list != NULL)
		{
			print_n_char(' ', lvl * 2);
			ft_putchar(';');
			ft_putchar('\n');
		}
	}
}
