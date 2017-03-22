#ifndef FTSH_H
# define FTSH_H

//# define FTSH_DEBUG

# include "shell_env.h"

t_shell_env		*init(int ac, char **av);
void			read_input(void);
void			break_input(void);
void			parse_input(void);
void			execute_tree(void);

#endif
