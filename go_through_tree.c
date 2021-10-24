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
    char **cmd_array;

    if (check_redir(ast))
    {
        heredoc_func(ast);
    }
    cmd_array = ft_split(ast->value, ' ');
    if (ft_strequal(cmd_array[0], "env"))
        env_builtin(data->env);
      else if (ft_strequal(cmd_array[0], "export"))
        export_builtin(cmd_array, &(data->env));
      else if (ft_strequal(cmd_array[0], "unset"))
        unset_builtin(cmd_array, &(data->env));
      else if (ft_strequal(cmd_array[0], "echo"))
        echo_builtin(cmd_array);
      else if (ft_strequal(cmd_array[0], "cd"))
        cd_builtin(cmd_array, &(data->env));
      else if (ft_strequal(cmd_array[0], "exit"))
        exit_builtin();
      else if (ft_strequal(cmd_array[0], "pwd"))
        pwd_builtin();
      else
        binary_command(cmd_array, &(data->env));
    free_array(cmd_array);
}