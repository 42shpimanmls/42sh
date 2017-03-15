#ifndef HISTORY_H
# define HISTORY_H

#define HISTFILE ".42sh_history"  // exported env variable dans les shells

/*typedef	struct s_hist_opt
{
	
}				t_hist_opt;
*/
/*
**		load_history.c
*/
void	load_history(t_shell_env *shell_env, char *filename);
void	print_history(t_history *history);

/*
**		history_del.c
*/

void	clear_history_list(t_history **history);
void	delete_history_entry(t_history **history, int offset);

/*
**		history_to_file.c
*/

void	hist_to_file(t_history *history, char *filename);


#endif
