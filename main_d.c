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

char **array_init(char *line)
{
	char **array;
	int j;
	int ind;
	char *tmp;
	int i = -1;

	ind = 0;
	j = 0;
	while (line[++i])
	{
		if (line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			tmp = ft_substr(line, 0, i);
			break ;
			printf("tmp = %s\n", tmp);
		}
	}
	array = (char **)malloc(sizeof(char *) * ft_strlen(tmp));
	if (!array)
		return (NULL);
	while (tmp[j])
	{
		if (tmp[j] == ' ')
		{
			array[ind] = ft_substr(tmp, 0, j);
			tmp = ft_substr(tmp, j + 1, ft_strlen(tmp) - j);
			printf("array[i] = %s\n", array[ind]);
			ind++;
			j = -1;
		}
		j++;
	}
	return (array);
}

int main(int argc, char **argv, char **envp)
{
	char	**get_env;
	char	*line;
	char	**array;
	t_data	*data;

	data = create_data(env, argc, argv);
	get_env = get_envp(envp);
	// while (1)
	// {d
		// line = readline("> ");
		line = ft_strdup("echo < test > test2");
		array = array_init(line);
		parsing(line, get_env);
		printf("%s\n", line);
		// print_tree_rec(ast, 0);
	// }

}