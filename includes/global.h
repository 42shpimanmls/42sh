#include <stdlib.h>
#include <libft.h>

typedef struct			s_history
{
	char				*line;
	struct s_history	*prec;
	struct s_history	*next;
}						t_history;

typedef struct s_global
{
	char		**env;
	t_history	*history;
	// variables locales (var, value)
} t_global;