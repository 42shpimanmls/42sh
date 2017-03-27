#include "parse_input/syntax_tree.h"
#include "errors.h"
#include "utils.h"
#include <libft.h>
#include "execute_syntax_tree.h"

#include <stdio.h>

t_error_id	execute_simple_command(t_simple_command *cmd, size_t lvl)
{
	t_error_id ret;

	ret = NO_ERROR;
	if (cmd != NULL)
	{
		// EXECUTION CORE
		//expand_words(&cmd->argv);
		//redirect(cmd->redirections);
		//expand_assignments_values(cmd->assignments);
		ret = execute_builtin(cmd, lvl);
		if (ret == NO_SUCH_BUILTIN)
		{
			ret = NO_ERROR;
			print_n_char(' ', (lvl) * 2);
			dprintf(1, "executing cmd %s\n", cmd->argv[0]);
			//ret = execute_file(cmd);
			print_n_char(' ', (lvl) * 2);
			dprintf(1, "done executing cmd %s, %s\n", cmd->argv[0]
				, ret == NO_ERROR ? "ok" : "error");
			// WAIT FOR EXECUTION
		}
	}
	return (ret);
}

t_error_id	execute_pipeline(t_simple_command *pipeline, size_t lvl)
{
	t_error_id		ret;

	if (pipeline == NULL)
		return (NO_ERROR);
	if (pipeline->next == NULL)
		return (execute_simple_command(pipeline, lvl));
	print_n_char(' ', (lvl) * 2);
	dprintf(1, "executing pipeline\n");
	print_n_char(' ', (lvl) * 2);
	dprintf(1, "is not supported\n");
	exit(EXIT_FAILURE);
	while (pipeline != NULL)
	{
		// should do pipeline stuff here
		ret = execute_simple_command(pipeline, lvl + 1);
		pipeline = pipeline->next;
	}
	// should wait for execution here
	print_n_char(' ', (lvl) * 2);
	dprintf(1, "done executing pipeline, %s\n", ret == NO_ERROR ? "ok" : "error");
	return (ret);
}
