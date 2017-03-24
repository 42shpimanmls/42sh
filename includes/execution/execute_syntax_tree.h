#ifndef EXECUTE_SYNTAX_TREE_H
#define EXECUTE_SYNTAX_TREE_H

#include "errors.h"
#include "parse_input/syntax_tree.h"

t_error_id	execute_command_list(t_command_list *cmd_list);
t_error_id	execute_pipeline(t_simple_command *pipeline, size_t lvl);
t_error_id	execute_builtin(t_simple_command *cmd, size_t lvl);

#endif
