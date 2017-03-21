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

#endif
