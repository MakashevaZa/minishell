#include "minishell.h"

t_cmd  *new_list(void)
{
    t_cmd  *list;

    list = (t_cmd *)malloc(sizeof(t_cmd));
    if(!list)
        return (NULL);
    list->args = (char **)malloc(sizeof(char *));
    if (!list->args)
        return (NULL);
    list->pipe = 0;
    list->redir = 0;
    list->size = 0;
    list->next = NULL;
}