#include "expansion.h"
#include "break_input/substitution.h"
#include <stdlib.h>
#include <libft.h>
#include "strlist.h"
#include "utils.h"
#include "errors.h"
#include "execution/pipe.h"
#include <stdio.h>
#include "shell_env.h"
#include "abstract_list.h"
#include "break_input/quoting.h"

char					*strlist_to_str(t_strlist const *list)
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
	strlist_append(strlist_addr, tmp, false);
	free(tmp);
}

static t_strlist					*fd_to_str(int fd, char quoted)
{
	size_t const	bufsz = 4096;
	char			buffer[bufsz];
	t_strlist		*list;
	int				ret;
	// char			*result;

	list = NULL;
	while ((ret = read(fd, buffer, bufsz - 1)) > 0)
	{
		buffer[ret] = '\0';
		if (quoted & IS_QU_DOUBLE)
			strlist_append(&list, buffer, false);
		else
			strlist_append(&list, buffer, true);
	}
	// result = strlist_to_str(list);
	// strlist_delete(&list);
	return (list);
}

// static void					rm_trailing_newlines(char *str)
// {
// 	size_t	len;
// 	len = ft_strlen(str);
// 	while (len-- > 0 && str[len] == '\n')
// 		str[len] = '\0';
// }

static void					add_substitution(t_strlist **strlist_addr
										, char const *start, char const *end, char quoted)
{
	int					pipefds[2];
	char				**argv;
	extern char			**environ;
	char				**environ_backup;
	t_strlist			*tmp;

	argv = (char*[]){ft_strdup(get_shell_env()->path_to_42sh), "-c"
											, strdup_until(start, end), NULL};
	pipe(pipefds);
	environ_backup = environ;
	environ = get_variables_for_execution(NULL);
	if (enter_subshell() == FORKED_IN_CHILD)
	{
		close(pipefds[0]);
		dup2(pipefds[1], STDOUT_FILENO);
		close(pipefds[1]);
		execvp(argv[0], argv);
		fatal_error("failed to execute recursively in add_substitution");
	}
	else
	{

		close(pipefds[1]);
		tmp = fd_to_str(pipefds[0], quoted);
		// rm_trailing_newlines(tmp);
		list_concat((t_abstract_list**)strlist_addr, (t_abstract_list*)tmp);
		// strlist_append(strlist_addr, tmp, true);
		// free(tmp);
		wait_for_childs();
	}
	ft_freetabchar(environ);
	environ = environ_backup;
	free(argv[0]);
	free(argv[2]);
}


/*

case double-quoted => substitution but no field splitting
(sh $ "`ls`" != sh $ `ls`)

static void 				handle_quotes(char const **word, char *quoted)
{
	if (**word == '\\')
		*word += 2;
	else if (**word == '\'')
	{
		if (*quoted & IS_QU_SIMPLE)
			*quoted -= IS_QU_SIMPLE;
		else
			*quoted |= IS_QU_SIMPLE;
	}
	else if (**word == '\"')
	{
		if (*quoted & IS_QU_DOUBLE)
			*quoted -= IS_QU_DOUBLE;
		else
			*quoted |= IS_QU_DOUBLE;
	}
}
*/

static t_strlist			*split_subsitutions(char const *word)
{
	char const	*passv_str_start;
	char const	*subst_end;
	t_strlist	*result;
	char		quoted;

	quoted = 0;
	passv_str_start = NULL;
	result = NULL;
	while (*word != '\0')
	{
		/*
		if (is_quote(*word))
			handle_quotes(&word, &quoted);*/
		if (is_substitution_start(word))
		{
			if (passv_str_start != NULL)
				add_passive_string(&result, passv_str_start, word - 1);
			subst_end = find_substitution_end(word + 1);
			if (get_error() != NO_ERROR)
				// same as quotes - go back to read_input
				fatal_error("substitution end not found in split_subsitutions(), a substitution hasn't been correctly recognized before being expanded");
			add_substitution(&result, word + 1, subst_end, quoted);
			if (get_error() != NO_ERROR)
				fatal_error("error in add_substitution() in split_subsitutions()");
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

t_strlist						*command_substition(char const *word)
{
	t_strlist	*strlist;
	// char		*result;

	strlist = split_subsitutions(word);
	// result = strlist_to_str(strlist);
	// strlist_delete(&strlist);
	return (strlist);
}
