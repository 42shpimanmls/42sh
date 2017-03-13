#include "event_callback_def.h"
#include <libft.h>
#include <stdio.h>
#include "utils.h"

void								print_event_callback_def(
	t_event_callback_def const *def)
{
	if (def != NULL)
	{
		printf("id:%d, name:\"%s\", str:\"", def->id, def->name);
		print_non_ascii_str(def->str);
		printf("\", callback:%p\n", def->callback);
	}
}
