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

char *skip_space(char *line, int *i)
{
	int j = *i;
	char *tmp;
	char *tmp2;
	char *tmp3;
	char *res;

	// i = 0;
	// while (line[*i] != ' ')
	// 	*i++;
	tmp = ft_substr(line, 0, j + 1);
	while (line[*i] == '_')
		(*i)++;
	// tmp3 = ft_substr(line, )
	tmp2 = ft_strdup(line + *i);
	tmp = ft_strjoin(tmp, tmp2);
	printf("res = %s\n", tmp);
	return (tmp);
}

void pre_parse(char *line)
{
	int i;
	char *tmp;
	char *tmp2;
	char *res;

	i = 0;
	while (line[i])
	{
		if (line[i] == '_')
		{
			tmp = ft_substr(line, 0, i + 1);
			while (line[i] == '_')
				(i)++;
	// tmp3 = ft_substr(line, )
			tmp2 = ft_strdup(line + i);
			line = ft_strjoin(tmp, tmp2);
			printf("res = %s\n", tmp);
		}
			// line = skip_space(line, &i);
		else
			i++;
	}
	
}

// enum built_in {
// 	echo,
// 	cd,
// 	pwd,
// 	export,
// 	unset,
// 	env,
// 	exit
// };

int main(int argc, char **argv, char **envp)
{
	char **get_env;
	char *line;
	// t_ast *ast;

	get_env = get_envp(envp);
	// while (1)
	// {
		// ast = create_node(ast);
		// line = readline("> ");
		line = ft_strdup("echo_____hey_____hey");
		pre_parse(line);
		// line = parsing(line, get_env);
		// printf("%s\n", line);
	// }

}