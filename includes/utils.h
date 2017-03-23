#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdbool.h>

void						print_non_ascii_str(char const *str);
void						print_non_ascii_char(char c);
void						event_callback_test(void);
char						*strdup_until(char const *src, char const *stop);
bool						is_posix_blank(char c);
void						print_n_char(char c, size_t n);
bool						str_is_digits(char const *str);
bool						is_circumflex(char c);
bool						is_bang(char c);
char						*str_in_str(char *find, char *str, bool must_start);
void						str_join_with_space(char **str, char *to_join);
size_t						number_len(char *str);
void						free_ptr_array(void *ptr_array);


#endif
