#include "errors.h"
#include "history_substitutions.h"

static void	set_hist_entry(char **hist_entry, char *str, \
							t_uint start, t_uint *end)
{
	if (!*hist_entry)
	{
		if (!((*hist_entry) = get_history_entry(&str[start + 1], end)))
			error_builtin(NULL, ft_strsub(str, start, *end - start), \
							EV_NOT_FOUND);
		if (str[*end])
			(*end)++;
	}
	else
		*end += 2;
}

int			start_substitution(char **str, t_uint *start, char *hist_entry)
{
	t_uint	end;
	int		should_run;
	bool	quote;

	should_run = 1;
	quote = 0;
	end = *start;
	set_hist_entry(&hist_entry, *str, *start, &end);
	if ((*str)[end] && start_word_designator((*str)[end]))
		get_entry_word(&hist_entry, &(*str)[end], &end);
	if (end < ft_strlen(*str) && (*str)[end] == ':')
		should_run = apply_modifiers(&(*str)[end], &hist_entry, &end, &quote);
	if (get_error() == NO_ERROR)
	{
		if (quote)
			quote_word(&hist_entry);
		perform_substitution(str, hist_entry, start, end);
		return (should_run);
	}
	ft_strdel(&hist_entry);
	return (-1);
}
