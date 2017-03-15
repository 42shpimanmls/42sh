#ifndef HISTORY_H
# define HISTORY_H

#define HISTFILE ".42sh_history"  // exported env variable dans les shells

void	load_history(t_shell_env *shell_env, char *filename);
void	print_history(t_history *history);
void	clear_history_list(t_history **history);
void	delete_history_entry(t_history **history, int offset);

#endif