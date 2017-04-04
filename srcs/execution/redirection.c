#include "redirection.h"

#define REDIRECT_DEBUG

int 				*save_stdin_stdout()
{
	static int std[2];

	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	return (std);
}

void				restore_stdin_stdout(int *std)
{
	dup2(std[0], STDIN_FILENO);
	close(std[0]);
	dup2(std[1], STDOUT_FILENO);
	close(std[1]);
}

t_error_id			redirect(t_redirection *redirections)
{
	t_error_id 	ret;
	int 		file_fd;

	ret = NO_ERROR;
	while (redirections)
	{
		if (redirections->type == REDIR_OUTPUT)
			file_fd = open(redirections->word, O_RDWR | O_CREAT | O_TRUNC, 0666);
		else if (redirections->type == APPEND_OUTPUT)
			file_fd = open(redirections->word, O_RDWR | O_CREAT | O_APPEND, 0666);
		else
			file_fd = open(redirections->word, O_RDONLY);
		if (file_fd < 0)
		{
			set_file_error(redirections->word);
			// print_error_msg(get_error());
			ret = get_error();
			print_file_error(ret, redirections->word);
			// should also print the file name
			return (ret);
		}
		else
		{
			dup2(file_fd, redirections->n);
			close(file_fd);
		}
		redirections = redirections->next;
	}
	return (ret);
}