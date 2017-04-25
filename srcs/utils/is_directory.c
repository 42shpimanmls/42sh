#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>

bool			is_directory(char const *path)
{
	struct stat		buf;
	int				ret;

	ret = stat(path, &buf);
	if (ret == -1)
		return (false);
	else
		return (S_ISDIR(buf.st_mode));
}
