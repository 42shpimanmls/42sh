#include "test_utils.h"

#include "shell_env.h"
#include "history_substitutions.h"
#include "init/init.h"
#include "ftsh.h"

#define HIST_TESTFILE "history_test_file"


void	bang_substitutions()
{
	char *av[] = {"./42sh"};
	char *str = ft_strdup("!!");

	init(1, av);
	load_history(get_shell_env(), HIST_TESTFILE);

	history_substitution(&str);

	CU_ASSERT_STRING_EQUAL(str, "un deux trois quatre cinq");
}