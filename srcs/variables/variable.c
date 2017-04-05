#include "shell_env.h"
#include "utils.h"
#include "abstract_list.h"

t_variable	*create_variable(char *name, char *value, bool exported)
{
	t_variable *v;

	v = memalloc_or_die(sizeof(t_variable));
	v->name = ft_strdup(name);
	v->value = ft_strdup(value);
	v->exported = exported;
	v->next = NULL;
	return (v);
}

void		print_variable(t_variable *v)
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

bool		check_if_variable_exist(t_variable *v, char *name)
{
	while (v)
	{
		if (!ft_strcmp(v->name, name))
		{
			return (true);
		}
		v = v->next;
	}
	return (false);
}

void		free_variable(t_variable *list)
{
	if (list)
	{
		free(list->name);
		free(list->value);
		free(list);
	}
}

void		delete_variable(t_variable **var)
{
	free_variable(*var);
	*var = NULL;
}

void		delete_all_variables(t_variable **var)
{
	t_variable	*it;
	t_variable	*tmp;

	it = *var;
	while (it)
	{
		tmp = it->next;
		free_variable(it);
		it = tmp;
	}
	*var = NULL;
}

void		pop_variable_by_name(t_variable **list, char *name)
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
			free_variable(lst);
			return ;
		}
		addr = &(*addr)->next;
		lst = *addr;
	}
}

t_variable *copy_variable(t_variable *e)
{
	t_variable	*tmp;
	t_variable	**ee = NULL;
	tmp = e;
	while (tmp)
	{
		t_variable	*var = create_variable(tmp->name, tmp->value, true);
			list_push_back((t_abstract_list**)&ee \
				, (t_abstract_list*)var);

		tmp = tmp->next;
	}
	return (*ee);
}