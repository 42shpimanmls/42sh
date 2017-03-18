#ifndef HISTORY_H
# define HISTORY_H

#include "execution/builtins/builtin_def.h"



/**DELETE*/

// bool	str_is_digits(char const *str);






#define HISTFILE ".42sh_history"  // exported env variable in shells


typedef	struct s_hist_opt
{
	bool	c;
	bool	d;
	bool	a;
	bool	n;
	bool	r;
	bool	w;
	bool	p;
	bool	s;
	char	*offset;
	char	*filename;
	char	**args;
}				t_hist_opt;

/*
**		load_history.c
*/
void	load_history(t_shell_env *shell_env, char *filename);

/*
**		history_del.c
*/

void	clear_history_list(t_history **history);
void	delete_history_entry(t_history **history, char *offset);

/*
**		history_to_file.c
*/

void	hist_to_file(t_history *history, char *filename);

/*
**		history.c
*/

void	print_history(t_history *history, int start);
BUILTIN_RET	builtin_history(BUILTIN_ARGS);


/*
**		history_errors.c
*/

void	history_error(int code, char *error);


#endif
