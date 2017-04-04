#include "execute_syntax_tree.h"
#include <libft.h>

int 			*save_stdin_stdout();
t_error_id		redirect(t_redirection *redirections);
void			restore_stdin_stdout(int *std);
