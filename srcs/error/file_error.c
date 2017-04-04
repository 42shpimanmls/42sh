#include "errors.h"
#include <unistd.h>
#include <sys/stat.h>

static char	get_file_type(mode_t mode)
{
	char	type;

	if (S_ISLNK(mode))
		type = 'l';
	else if (mode & S_IFREG)
		type = '-';
	else if (S_ISBLK(mode))
		type = 'b';
	else if (mode & S_IFDIR)
		type = 'd';
	else if (S_ISCHR(mode))
		type = 'c';
	else
		type = 'p';
	if (S_ISSOCK(mode))
		type = 's';
	return (type);
}

void 		set_file_error(char *file) // , char *expected_types
{
	struct stat 	stats;

	if (access(file, F_OK) < 0)
		set_error(NO_SUCH_FILE);
	else if (access(file, R_OK | W_OK | X_OK) < 0)
		set_error(PERM_DENIED);
	else
	{
		lstat(file, &stats);
		if (get_file_type(stats.st_mode) == 'd')
			set_error(IS_DIR);
	}
}
