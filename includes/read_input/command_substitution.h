#ifndef COMMAND_SUBSTITUTION_H
# define COMMAND_SUBSTITUTION_H

void	add_passive_string(t_strlist **strlist_addr, char const *start,
		char const *end);
char	*fd_to_str(int fd);
void	rm_trailing_newlines(char *str);

#endif
