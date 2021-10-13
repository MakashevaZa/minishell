#include "minishell.h"

char **get_envp(char **envp)
{
	char **data;
	int i;

	i = 0;
	while (envp[i])
		i++;
	data = (char **)malloc(sizeof(char *) * (i + 1));
	if (!data)
	{
		write(1, "Error in memory allocation\n", ft_strlen("Error in memory allocation\n"));
		exit (1);
	}
	i = 0;
	while (envp[i])
	{
		data[i] = ft_strdup(envp[i]);
		i++;
	}
	// data[i] = NULL;
	return(data);
}

enum built_in {
	echo,
	cd,
	pwd,
	export,
	unset,
	env,
	// exit,
};


t_cmd *get_args(char *line)
{
	char *tmp;
	t_cmd *a;

	int i = 0;
	a = NULL;
	while (line[i])
	{
		if (line[i] != ' ' && line[i + 1] == ' ')
		{
			tmp = ft_substr(line, 0, i + 1);
			if (a == NULL)
				a = new_list(tmp);
			else
				add_back(a, tmp);
			line = ft_strdup(line + i + 2);
			// printf("line = %s|\n", line);
			i = 0;
		}
		// else if (line[i] == '>' || line[i] == '<')
		// {
		// 	tmp = ft_substr(line, 0, i);
		// 	if (a == NULL)
		// 		a = new_list(tmp);
		// 	else
		// 		add_back(a, tmp);
		// 	tmp = ft_substr(line, i, i);
		// 	printf("tmp=%s\n", tmp);
		// 	add_back(a, line[i]);
		// 	line = ft_strdup(line + i + 1);
		// 	i = 0;
		// }
		else
			i++;
		// printf("line = |%s|\n", line);
	}
	if (a == NULL)
		a = new_list(line);
	else
		add_back(a, line);
	// while (a != NULL)
	// {
	// 	printf("a->value = %s a->prior = %d\n", a->value, a->prior);
	// 	a = a->next;
	// }
	return (a);
}



int main(int argc, char **argv, char **envp)
{
	char **get_env;
	char *line;
	// char **array;
	t_ast *ast;
	t_cmd *list;
	list = NULL;

	ast = NULL;
	get_env = get_envp(envp);
	// array = (char **)malloc(sizeof(char *));
	// while (1)
	// {
		// ast = create_node(ast);
		// line = readline("> ");
		// list = new_list();
		line = ft_strdup("echo hey there > a");
		// pre_parse(line);
		line = parsing(line, get_env);
		// dfa(line);
		list = get_args(line);
		while (list != NULL)
		{
			if (ast == NULL)
				ast = create_node(list->value);
			else
				add_value(&ast, list->value);
			list = list->next;
		}
		// while (list != NULL)
		// {
		// 	printf("value = |%s| prior = |%d|\n", list->value, list->prior);
		// 	list = list->next;
		// }
		printf("%s\n", line);
		print_tree_rec(ast, 0);
	// }

}