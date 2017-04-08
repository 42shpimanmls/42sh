#ifndef HISTORY_OPTIONS_H
# define HISTORY_OPTIONS_H

#include <stdbool.h>

typedef	struct 	s_hist_opt
{
	char		anrw;
	bool		c;
	bool		d;
	bool		p;
	bool		s;
	char		*offset;
	char		*filename;
	char		**args;
	int 		ac;
}				t_hist_opt;

void			get_hist_options(char *c, t_hist_opt *options);
void			free_history_options(t_hist_opt *options);

#endif
