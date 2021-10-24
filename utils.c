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

int check_redir(t_ast *ast)
{
	if (ft_strcmp(ast->value, ">") == 0 || ft_strcmp(ast->value, ">>") == 0 || ft_strcmp(ast->value, "<") == 0 || ft_strcmp(ast->value, "<<") == 0)
		return (1);
	return (0);
}
