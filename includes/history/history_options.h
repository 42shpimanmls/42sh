#ifndef HISTORY_OPTIONS_H
# define HISTORY_OPTIONS_H

#include <stdbool.h>

typedef	struct 	s_hist_opt
{
	bool		c;
	bool		d;
	bool		a;
	bool		n;
	bool		r;
	bool		w;
	bool		p;
	bool		s;
	char		*offset;
	char		*filename;
	char		**args;
}				t_hist_opt;

int				get_hist_options(char *c, t_hist_opt *options);
void			print_history_options(t_hist_opt *options);
void			free_history_options(t_hist_opt *options);

#endif
