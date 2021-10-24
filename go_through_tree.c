#include "minishell.h"

static void write_to_tmp(t_ast *ast, int fd)
{
    char *buf;
    while (1)
    {
        buf = readline("> ");
        if (!buf)
            
        ft_strequal(buf, ast->right);
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
    int pid;
    int i;

    if (check_redir(ast))
    {
        // pid = fork();
        // signal(SIGINT, SIG_IGN);
    //     if (pid == 0)
    //     {
    //         // sigHDHandler();
            heredoc_func(ast);
    //     }
    //     waitpid(pid, &i, 0);
    //     if (WTERMSIG(i) == SIGINT)
    //         exit(1);
    //     else
    //         exit(i / 256);
    }
}