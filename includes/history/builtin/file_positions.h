#ifndef FILE_POSITIONS_H
# define FILE_POSITIONS_H

void						update_file_position(char *filename, \
												int new_position);
t_file_position				*get_file_position(char *filename);
void						print_file_positions();

#endif
