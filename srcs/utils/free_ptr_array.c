#include "utils.h"

void	free_ptr_array(void *ptr_array)
{
	void	**it;

	if (ptr_array != NULL)
	{
		it = ptr_array;
		while (*it != NULL)
		{
			free(*it);
			it++;
		}
		free(ptr_array);
	}
}
