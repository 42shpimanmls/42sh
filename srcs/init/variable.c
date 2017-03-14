#include "shell_env.h"
#include "utils.h"

t_variable *create_variable(char *name, char *value, bool exported)
{
	t_variable *v;

	v = (t_variable *)malloc_or_die(sizeof(t_variable));
	v->name = ft_strdup(name);
	v->value = ft_strdup(value);
	v->exported = exported;
	v->next = NULL;
	return (v);
}

void print_variable(t_variable *v)
{
	while (v)
	{
		ft_printf("Name: \"%s\"	", v->name);
		ft_printf("Value: \"%s\"	", v->value);
		if (v->exported)
			ft_printf("FOR EXPORT\n");
		v = v->next;
	}
}

void free_variable(t_variable **list)
{
	if (*list)
	{
		free((*list)->name);
		free((*list)->value);
		free((*list));
	}
}

void pop_variable_by_name(t_variable **list, char *name)
{
	t_variable *lst;
	t_variable **addr;

	lst = *list;
	addr = list;
	while (lst)
	{
		if (!ft_strcmp(lst->name, name))
		{
			*addr = lst->next;
			free_variable(&lst);
			return ;
		}
		addr = &(*addr)->next;
		lst = *addr;
	}
}

void list_push_back(t_variable **list, t_variable *new)
{
	t_variable *tmp;

	if (*list == NULL)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}	
}
