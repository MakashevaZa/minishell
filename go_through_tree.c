#include "minishell.h"

static void write_to_tmp(t_ast *ast, int fd)
{
    char *buf;

    while ((buf = readline("> ")) != NULL && !ft_strequal(buf, ast->right)) 
    {
        if (ft_strlen(buf) > 0) 
            ft_putendl_fd(buf, fd);
        free(buf);
    }
}

static void heredoc_func(t_ast *ast)
{
    int here;
    char *stop;
    int i;
    char *name;

    i = 0;
    
    if (!ast)
        return ;
    if (ft_strequal(ast->value, "<<"))
    {
        name = ft_strjoin("/tmp/.tmp_heredoc", ft_itoa(i));
        here = open(name, O_CREAT | O_TRUNC | O_WRONLY,
				S_IRUSR | S_IRGRP | S_IWUSR | S_IROTH);
        write_to_tmp(ast->right, here);
        i++;
        free(name);
        close(here);        
    }
    heredoc_func(ast->left);
    heredoc_func(ast->right);
}

void go_through_tree(t_ast *ast, t_data *data)
{
    heredoc_func(ast);
}