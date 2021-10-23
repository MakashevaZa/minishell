#include "minishell.h"

static void heredoc_func(t_ast *ast)
{
    int here;

    if (!ast)
        return ;
    if (ft_strequal(ast->value, "<<"))
        here = open("", );
    heredoc_func(ast->left);
    heredoc_func(ast->right);
}

void go_through_tree(t_ast *ast, t_data *data)
{
    heredoc_func(ast);

}