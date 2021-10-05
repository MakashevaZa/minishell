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
		if (ft_strcmp(value, ">") == 0)
			node->prior = 2;
		if (ft_strcmp(value, "|") == 0)
			node->prior = 1;
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

t_ast*	insert_val(t_ast **ast, char *value)
{
	t_ast *tmp;
	int prior;

	tmp = *ast;
	if (tmp == NULL)
	{
		*ast = create_node(value);
		return (NULL);
	}
	// if (value == tmp->value)
	// 	return NULL;
	if (ft_strcmp(value, ">") == 0)
		prior = 2;
	else if (ft_strcmp(value, "|") == 0)
		prior = 1;
	else
		prior = 0;
	if (prior < tmp->prior)
		return (insert_val(&(tmp->left), value));
	else
		return (insert_val(&(tmp->right), value));
		
}


// int main()
// {
// 	t_ast *ast = NULL;

// 	insert_val(&ast, "echo");
// 	insert_val(&ast, "hey");
// 	insert_val(&ast, ">");
// 	insert_val(&ast, "a");
// 	// insert_val(&ast, ">", 2);
// 	// insert_val(&ast, "|", 1);
	
// 	print_tree_rec(ast, 0);

// 	return (0);
// }