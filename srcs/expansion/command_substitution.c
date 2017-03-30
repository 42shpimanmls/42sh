#include "expansion.h"
#include "break_input/substitution.h"
#include <stdlib.h>
#include <libft.h>
#include "strlist.h"
#include "utils.h"
#include "errors.h"
#include "execution/pipe.h"
#include <stdio.h>

static char					*strlist_to_str(t_strlist const *list)
{
	char	*result;

	result = NULL;
	while (list != NULL)
	{
		result = ft_strjoinf(result, list->str, 1);
		list = list->next;
	}
	return (result);
}

static void					add_passive_string(t_strlist **strlist_addr
										, char const *start, char const *end)
{
	char	*tmp;

	tmp = strdup_until(start, end);
	strlist_append(strlist_addr, tmp);
	free(tmp);
}

static char					*fd_to_str(int fd)
{
	size_t const	bufsz = 4096;
	char			buffer[bufsz];
	t_strlist		*list;
	int				ret;
	char			*result;

	list = NULL;
	while ((ret = read(fd, buffer, bufsz - 1)) > 0)
	{
		buffer[ret] = '\0';
		strlist_append(&list, buffer);
	}
	result = strlist_to_str(list);
	strlist_delete(&list);
	return (result);
}

static void					rm_trailing_newlines(char *str)
{
	size_t	len;
	len = ft_strlen(str);
	while (len-- > 0 && str[len] == '\n')
		str[len] = '\0';
}

static char					*get_ftsh_path(void)
{
	return ("./42sh");
}

static void					add_substitution(t_strlist **strlist_addr
										, char const *start, char const *end)
{
	int					pipefds[2];
	char				**argv;
	extern char			**environ;
	char				**environ_backup;
	char				*tmp;

	argv = (char*[]){get_ftsh_path(), "-c", strdup_until(start, end), NULL};
	pipe(pipefds);
	environ_backup = environ;
	environ = get_variables_for_execution(NULL);
	if (enter_subshell() == FORKED_IN_CHILD)
	{
		close(pipefds[0]);
		dup2(pipefds[1], STDOUT_FILENO);
		close(pipefds[1]);
		execvp(argv[0], argv);
		print_n_char_fd(' ', (0) * 2, 2);
		dprintf(2, "error while executing file: ");
		perror("");
		exit(EXIT_FAILURE);
	}
	else
	{

		close(pipefds[1]);
		tmp = fd_to_str(pipefds[0]);
		rm_trailing_newlines(tmp);
		strlist_append(strlist_addr, tmp);
		free(tmp);
		wait_for_childs();
	}
	ft_freetabchar(environ);
	environ = environ_backup;
	free(argv[2]);
}

static t_strlist			*split_subsitutions(char const *word)
{
	char const	*passv_str_start;
	char const	*subst_end;
	t_strlist	*result;

	passv_str_start = NULL;
	result = NULL;
	while (*word != '\0')
	{
		if (is_substitution_start(word))
		{
			if (passv_str_start != NULL)
				add_passive_string(&result, passv_str_start, word - 1);
			subst_end = find_substitution_end(word + 1);
			if (get_error() != NO_ERROR)
			{
				ft_putendl_fd("This shouldn't have happened", 2);
				exit(-1);
			}
			add_substitution(&result, word + 1, subst_end);
			if (get_error() != NO_ERROR)
			{
				ft_putendl_fd("Error in add_substitution", 2);
				exit(-1);
			}
			word = subst_end + 1;
		}
		else
		{
			if (passv_str_start == NULL)
				passv_str_start = word;
			word++;
		}
	}
	if (passv_str_start != NULL)
		add_passive_string(&result, passv_str_start, word);
	return (result);
}

char						*command_substition(char const *word)
{
	t_strlist	*strlist;
	char		*result;

	strlist = split_subsitutions(word);
	result = strlist_to_str(strlist);
	strlist_delete(&strlist);
	return (result);
}
