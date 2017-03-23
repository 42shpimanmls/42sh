#include "event_callback_def.h"
#include <libft.h>

static void	get_sub_string(EV_CB_ARGS)
{
	char *all;
	size_t start;
	size_t end;

	start = ed->selected_string_start;
	end = ed->selected_string_end;
	if (start > end)
	{
		end = ed->selected_string_start;
		start = ed->selected_string_end;
	}
	all = get_string_from_list(ed->string);
	free(ed->selected_string);
	ed->selected_string = ft_strsub(all, start, end - start);
	free(all);
}

static void	get_position(EV_CB_ARGS)
{
	if (!ed->in_selection)
	{
		ed->in_selection = true;
		ed->selected_string_start = ed->cursor_position;
	}
	else
	{
		ed->in_selection = false;
		ed->selected_string_end = ed->cursor_position;
	}
}

EV_CB_RET 	event_copy(EV_CB_ARGS)
{
	(void)ed;
	// ft_dprintf(2, "COPY");
	ed->cutorcp = COPY;
	get_position(ed);
}

EV_CB_RET 	event_cut(EV_CB_ARGS)
{
	(void)ed;
	// ft_dprintf(2, "CUT");
	ed->cutorcp = CUT;
	get_position(ed);
}

EV_CB_RET 	event_paste(EV_CB_ARGS)
{
	(void)ed;

	// ft_dprintf(2, "PASTE");
	if (ed->cutorcp == COPY)
	{
		get_sub_string(ed);

		//paste string
	}
	else if (ed->cutorcp == CUT)
	{
		get_sub_string(ed);

		//cut string
	}
	else { /* set_error(WTF);*/ }

	// ft_dprintf(2, "STRING ALL  : \"%s\"\n", get_string_from_list(ed->string));
	// ft_dprintf(2, "STRING CUT  : \"%s\"\n", ed->selected_string);
}
