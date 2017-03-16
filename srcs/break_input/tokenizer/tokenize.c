#include "token.h"
#include <stdlib.h>
#include "utils.h"
#include <libft.h>
#include "abstract_list.h"

typedef struct	s_tokenizer_context
{
	char const	*input;
	char const	*current_char;
	char const	*word_start;
	char const	*op_start;
	t_token		*result;
	char const	*last_backslash;
	char const	*simple_quote_end;
	char const	*double_quote_end;
}				t_tokenizer_context;

static char		*strdup_until(char const *src, char const *stop)
{
	char	*result;
	size_t	len;

	len = stop - src;
	result = memalloc_or_die(sizeof(char) * (len + 1));
	ft_strncpy(result, src, len);
	result[len] = '\0';
	return (result);
}

static void		delimit_token(t_tokenizer_context *context)
{
	char		*str;
	t_token		*token;
	char const	*start;

	if (context->op_start)
		start = context->op_start;
	else
		start = context->word_start;
	if (!start)
		return ;
	str = strdup_until(start, context->current_char);
	if (*str != '\0')
	{
		token = construct_token(str, *context->current_char);
		ft_putstr("DELIMITED: ");
		print_token(token);
		list_push_back((t_abstract_list**)&context->result
			, (t_abstract_list*)token);
	}
	free(str);
	context->op_start = NULL;
	context->word_start = NULL;
}

static bool		is_operator_part(t_tokenizer_context *context)
{
	char		*str;
	bool		result;
	char const	*start;

	if (context->op_start != NULL)
		start = context->op_start;
	else
		start = context->current_char;
	str = strdup_until(start, context->current_char + 1);
	if (get_matching_operator(str) != NULL)
		result = true;
	else
		result = false;
	free(str);
	return (result);
}

static bool		is_quote(char c)
{
	if (c == '\'' || c == '"' || c == '\\')
		return (true);
	return (false);
}

static bool		is_substition_op(char c)
{
	if (c == '`')
		return (true);
	return (false);
}

static bool		is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

static char const *find_simple_quote_end(t_tokenizer_context *context)
{
	char const *it;

	it = context->current_char + 1;
	while (*it != '\0')
	{
		if (*it == '\'')
			return (it);
		it++;
	}
	ft_putendl_fd("42sh: syntax error: missing simple quote end\n", 2);
	exit(1);
}

static char const *find_substitution_end(char const *str)
{
	if (*str == '`')
		str++;
	while (*str)
	{
		if (*str == '`')
			return (str);
		str++;
	}
	ft_putendl_fd("42sh: syntax error: missing backquote end\n", 2);
	exit(1);
}

static char const *find_double_quote_end(t_tokenizer_context *context)
{
	char const *it;
	char nc;

	it = context->current_char + 1;
	while (*it != '\0')
	{
		nc = *(it + 1);
		if (*it == '`')
			it = find_substitution_end(it);
		if (*it == '\\' && (nc == '`' || nc == '"' || nc == '\\' || nc == '\n'))
			it++;
		else if (*it == '"')
			return (it);
		it++;
	}
	ft_putendl_fd("42sh: syntax error: missing double quote end\n", 2);
	exit(1);
}

static void		apply_quoting(t_tokenizer_context *context)
{
	if (*context->current_char == '\\')
		context->last_backslash = context->current_char;
	else if (*context->current_char == '\'')
		context->simple_quote_end = find_simple_quote_end(context);
	else if (*context->current_char == '"')
		context->double_quote_end = find_double_quote_end(context);
}

static bool		is_double_quoted(t_tokenizer_context *context)
{
	char c;
	char nc;

	if (context->double_quote_end >= context->current_char)
	{
		c = *context->current_char;
		if (c == '`')
			return (false);
		else if (c == '\\')
		{
			nc = *(context->current_char + 1);
			if (nc == '`' || nc == '"' || nc == '\\' || nc == '\n')
				return (false);
		}
		return (true);
	}
	else
		return (false);
}

static bool		is_quoted(t_tokenizer_context *context)
{
	if (context->last_backslash != NULL
		&& (context->current_char == context->last_backslash
				|| context->current_char - 1 == context->last_backslash))
		return (true);
	if (context->simple_quote_end >= context->current_char)
		return (true);
	if (is_double_quoted(context))
		return (true);
	return (false);
}

#include <stdio.h>

static void		print_state(t_tokenizer_context *context)
{
	ft_putstr("'");
	print_non_ascii_char(*context->current_char);
	printf("'@%ld%s last_bsl@%ld sim_quo_end@%ld  dub_quo_end@%ld\n", context->current_char - context->input, is_quoted(context) ? " QUOTED" : ""
		, context->last_backslash ? context->last_backslash - context->input : -1
		, context->simple_quote_end ? context->simple_quote_end - context->input : -1
		, context->double_quote_end ? context->double_quote_end - context->input : -1);
}

static void		apply_rules(t_tokenizer_context *context)
{
	char c;


	c = *context->current_char;
	print_state(context);
	// rule 2
	if (context->op_start != NULL && !is_quoted(context)
		&& is_operator_part(context))
	{
		context->current_char++;
		ft_putstr("rule 2 aka ADD TO OPERATOR\n");
		return ;
	}
	// rule 3
	if (context->op_start != NULL && !is_operator_part(context))
	{
		delimit_token(context);
		ft_putstr("rule 3 aka DELIMIT OPERATOR\n");
		return ;
	}
	// rule 4
	if (is_quote(c) && !is_quoted(context))
	{
		apply_quoting(context);
		ft_putstr("rule 4 aka APPLY QUOTING\n");
		return ;
	}
	// rule 5 (incomplete !! recursion not handled)
	if (!is_quoted(context) && is_substition_op(c))
	{
		context->current_char = find_substitution_end(context->current_char + 1) + 1;
		ft_putstr("rule 5 aka ADD SUBSTITUTION TO WORD aka JUMP JUMP\n");
		return ;
	}
	// rule 6
	if (!is_quoted(context) && is_operator_part(context))
	{
		delimit_token(context);
		context->op_start = context->current_char;
		context->current_char++;
		ft_putstr("rule 6 aka START OPERATOR\n");
		return ;
	}
	// rule 7
	if (!is_quoted(context) && is_blank(c))
	{
		delimit_token(context);
		context->current_char++;
		ft_putstr("rule 7 aka SKIP BLANK\n");
		return ;
	}
	// rule 8
	if (context->word_start != NULL)
	{
		context->current_char++;
		ft_putstr("rule 8 aka ADD TO WORD\n");
		return ;
	}
	// rule 9
	if (c == '#')
	{
		while (*(context->current_char + 1) != '\0'
			&& *(context->current_char + 1) != '\n')
			context->current_char++;
		ft_putstr("rule 9 aka SKIP COMMENT\n");
		return ;
	}
	// rule 10
	context->word_start = context->current_char;
	context->current_char++;
	ft_putstr("rule 10 aka START WORD\n");
}

t_token			*tokenize(char const *input)
{
	t_tokenizer_context context;

	ft_bzero(&context, sizeof(t_tokenizer_context));
	context.input = input;
	if (context.input != NULL)
	{
		context.current_char = context.input;
		while (*context.current_char != '\0')
			apply_rules(&context);
		// rule 1
		print_state(&context);
		delimit_token(&context);
		ft_putstr("rule 1 aka I'M DONE MOTHERF***ERZ\n");
	}
	return (context.result);
}
