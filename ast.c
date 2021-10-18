#include "minishell.h"

t_ast*	create_first_node(char *value, char *command)
{
	t_ast* node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (node != NULL)
	{
		node->left = NULL;
		node->right = NULL;
		node->value = value;
		node->command = command;
		node->prior = 1;
	}
	return (node);
}

t_ast*	create_node(char *value)
{
	t_ast* node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (node != NULL)
	{
		node->left = NULL;
		node->right = NULL;
		node->value = value;
		if (ft_strcmp(value, ">") == 0 || ft_strcmp(value, "<") == 0)
        	node->prior = 3;
		else if (ft_strcmp(value, ">>") == 0 || ft_strcmp(value, "<<") == 0)
			node->prior = 3;
		else if (ft_strcmp(value, "|") == 0 )
			node->prior = 2;
		else
			node->prior = 0;
	}
	return (node);
}

void printtabs(int n)
{
	int i = 0;
	while (i < n)
	{
		printf("\t");
		i++;
	}
}

void print_tree_rec(t_ast *ast, int level)
{
	if (ast == NULL)
	{
		printtabs(level);
		printf("-----<empty>-----\n");
		return ;
	}
	printtabs(level);
	printf("value = %s command = |%s| prior = |%d|\n ", ast->value, ast->command, ast->prior);
	printtabs(level);

	printf("left\n");
	print_tree_rec(ast->left, level + 1);
	printtabs(level);

	printf("right\n");
	print_tree_rec(ast->right, level + 1);
	printtabs(level);
	printf("done\n");
}

void insert_left(t_ast **ast, char *value)
{
	t_ast *tmp = NULL;

	if (&(*ast)->left != NULL)
		insert_left(&(*ast)->left, value);
	if (!(*ast))
	{
		tmp = (t_ast *)malloc(sizeof(t_ast));
		tmp->value = value;
		tmp->left = NULL;
		tmp->right = NULL;
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
		(*ast) = tmp;
	}
}

void	add_value(t_ast **ast, char *value)
{
	t_ast *tmp;
	int prior;

	if (ft_strcmp(value, ">") == 0 || ft_strcmp(value, "<") == 0)
        prior = 3;
	else if (ft_strcmp(value, ">>") == 0 || ft_strcmp(value, "<<") == 0)
		prior = 3;
	else if (ft_strcmp(value, "|") == 0 )
		prior = 2;
	else if (check_arg(value))
		prior = 1;
	else
		prior = 0;
	if ((*ast)->prior == 3 && prior == 0)
		(*ast)->right = create_node(value);
	else if ((*ast)->prior == 3 && prior == 2)
	{
		tmp = create_node(value);
		tmp->left = *ast;
		*ast = tmp;
	}
	else if ((*ast)->prior == 2 && prior == 0)
		(*ast)->right = create_node(value);
	else if ((*ast)->prior > prior)
	{
		insert_left(&(*ast)->left,value);
	}
		else
		{
			tmp = create_node(value);
			tmp->left = *ast;
			*ast = tmp;
		}
}
