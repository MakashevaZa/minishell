#include "minishell.h"

t_ast*	create_node(int value)
{
	t_ast* node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (node != NULL)
	{
		node->left = NULL;
		node->right = NULL;
		node->value = value;
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
	printf("value = %d\n", ast->value);
	printtabs(level);

	printf("left\n");
	print_tree_rec(ast->left, level + 1);
	printtabs(level);

	printf("right\n");
	print_tree_rec(ast->right, level + 1);
	printtabs(level);
	printf("done\n");
}

t_ast*	insert_val(t_ast **ast, int value)
{
	t_ast *tmp;

	tmp = *ast;
	if (tmp == NULL)
	{
		*ast = create_node(value);
		return (NULL);
	}
	// if (value == tmp->value)
	// 	return NULL;
	if (value < tmp->value)
		return (insert_val(&(tmp->left), value));
	else
		return (insert_val(&(tmp->right), value));
		
}


// int main()
// {
// 	t_ast *ast = NULL;

// 	insert_val(&ast, 6);
// 	insert_val(&ast, 8);
// 	insert_val(&ast, 0);
// 	insert_val(&ast, 34);
// 	insert_val(&ast, 4);
// 	insert_val(&ast, 45);
	
// 	print_tree_rec(ast, 0);

// 	return (0);
// }