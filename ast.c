#include "minishell.h"

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
		else if (ft_strcmp(value, "|") == 0 )
			node->prior = 2;
		else if (check_arg(value))
			node->prior = 1;
		else
		{
			node->prior = 0;
		}
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
	printf("value = %s\n", ast->value);
	printtabs(level);

	printf("left\n");
	print_tree_rec(ast->left, level + 1);
	printtabs(level);

	printf("right\n");
	print_tree_rec(ast->right, level + 1);
	printtabs(level);
	printf("done\n");
}

// t_ast*	insert_val(t_ast **ast, char *value)
// {
// 	t_ast *tmp;
// 	int prior;

// 	tmp = *ast;
// 	if (tmp == NULL)
// 	{
// 		*ast = create_node(value);
// 		return (ast);
// 	}
// 	// if (value == tmp->value)
// 	// 	return (0);

// 	if (ft_strcmp(value, ">") == 0 || ft_strcmp(value, "<") == 0)
//         prior = 3;
//     else if (ft_strcmp(value, "|") == 0 )
//         prior = 2;
//     else if (check_arg(value))
//         prior = 1;
//     else
//     {
//         prior = 0;
//     }
// 	if (prior < tmp->prior)
// 		return (insert_val(&(tmp->left), value));
// 	else
// 		return (insert_val(&(tmp->right), value));
		
// }

void	add_value(t_ast **ast, char *value)
{
	t_ast *tmp;
	int prior;

	if (ft_strcmp(value, ">") == 0 || ft_strcmp(value, "<") == 0)
        prior = 3;
	else if (ft_strcmp(value, "|") == 0 )
		prior = 2;
	else if (check_arg(value))
		prior = 1;
	else
		prior = 0;
	// tmp = (t_ast *)malloc(sizeof(t_ast));
	// if (tmp != NULL)
	// {
		if ((*ast)->prior == 3 && prior == 0)
			(*ast)->right = create_node(value);
		else if ((*ast)->prior > prior)
		{
			// tmp = *ast;
			// while(tmp->left != NULL)
			// 	tmp = tmp->left;
			// tmp->left = create_node(value);
			// (*ast)->left = tmp->left;
			while ((*ast)->left != NULL)
				(*ast) = (*ast)->left;
			(*ast)->left = create_node(value);
		}
		else
		{
			tmp = create_node(value);
			tmp->left = *ast;
			*ast = tmp;
			// tmp->value = value;
			// tmp->right = NULL;
			// tmp->left = *ast;
			// *ast = tmp;
		}
	// }
}


// int main()
// {
// 	t_ast *ast = NULL;

// 	insert_val(ast, "echo");
// 	insert_val(ast, "hey");
// 	insert_val(ast, ">");
// 	insert_val(ast, "a");
// 	// insert_val(&ast, ">", 2);
// 	// insert_val(&ast, "|", 1);
	
// 	print_tree_rec(ast, 0);

// 	return (0);
// }