#ifndef FILE_POSITION_H
# define FILE_POSITION_H

typedef struct 				s_file_position
{
	struct s_file_position 	*next;
	char 					*filename;
	int 					position;
}							t_file_position;

void 						update_file_position(char *filename, \
												int new_position);
t_file_position				*get_file_position(char *filename);
void 						print_file_positions();

#endif
