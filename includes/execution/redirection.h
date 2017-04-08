#include "execute_syntax_tree.h"
#include <libft.h>

/*
** FILE_PERMISSION same as 644
*/

#define FILE_PERMISSION (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

int 			*save_stdin_stdout();
t_error_id		redirect(t_redirection *redirections);
void			restore_stdin_stdout(int *std);
