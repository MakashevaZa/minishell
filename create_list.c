#include "minishell.h"

 int check_arg(char *arg)
{
	if (ft_strcmp("echo", arg) == 0 || ft_strcmp("cd", arg) == 0
		|| ft_strcmp("pwd", arg) == 0 || ft_strcmp("export", arg) == 0
		|| ft_strcmp("unset", arg) == 0 || ft_strcmp("env", arg) == 0
		|| ft_strcmp("exit", arg) == 0)
		{
			return (1);
		}
	return (0);
}

t_cmd  *new_list(char *value)
{
    t_cmd  *list;

    list = (t_cmd *)malloc(sizeof(t_cmd));
    if(!list)
        return (NULL);
    list->value = value;
    list->next = NULL;
    list->prev = NULL;
    if (!(ft_strcmp(value, ">")) || (!(ft_strcmp(value, ">"))))
        list->prior = 3;
    else if (ft_strcmp(value, "|") == 0 )
        list->prior = 2;
    else if (check_arg(value))
        list->prior = 1;
    else
        list->prior = 0;
    return (list);
}

void	add_back(t_cmd *lst, char *value)
{
	t_cmd	*last;
	t_cmd	*tmp;

	tmp = (t_cmd *)malloc(sizeof(t_cmd));
	while (lst->next != NULL)
		lst = lst->next;
	last = lst;
	tmp->value = value;
    if (ft_strcmp(value, ">") == 0 || ft_strcmp(value, "<") == 0)
        tmp->prior = 3;
    else if (ft_strcmp(value, "|") == 0 )
        tmp->prior = 2;
    else if (check_arg(value))
        tmp->prior = 1;
    else
    {
        tmp->prior = 0;
    }
	tmp->next = NULL;
	last->next = tmp;
    tmp->prev = last;
}