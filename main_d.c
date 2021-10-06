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

// int redirection_pars(char *line, int i)
// {
// 	while (line[i])
// 	{
// 		line[i] == 
// 	}
// }

int check_char(char *line, char ch, int i)
{
	while (line[i])
	{
		if (line[i] == ch)
			return (1);
		(i)++;
	}
	return (0);
}

char *single_quote_parse(char *line, int *i)
{
	int j = *i;
	char *tmp;
	char *tmp2;
	char *tmp3;
	if (check_char(line, '\'', j + 1) == 1)
	{
		while (line[++(*i)])
		{
			if (line[(*i)] == '\'')
				break ;
		}
		tmp = ft_substr(line, 0, j);
		tmp2 = ft_substr(line, j + 1,  *i - j - 1);
		tmp3 = ft_strdup(line + *i + 1);
		tmp = ft_strjoin(tmp, tmp2);
		tmp = ft_strjoin(tmp, tmp3);
		(*i)--;
	}
	else
		return (line);
	return (tmp);
}
char	*slesh_parse(char *line, int *i)
{
	int j = *i;
	char *tmp;
	char *tmp2;
	char *tmp3;

	tmp = ft_substr(line, 0, j + 1);
	printf("tmp = %s\n", tmp);
	tmp2 = ft_substr(line, j + 1,  *i -j - 1);
	printf("tmp2 = %s\n", tmp2);
	// tmp3 = ft_strdup(line + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	// tmp = ft_strjoin(tmp, tmp3);
	free(line);
	++(*i);
	return (tmp);
}

char	*double_quote_parse(char *line, int *i)
{
	int j = *i;
	char *tmp;
	char *tmp2;
	char *tmp3;

	if (check_char(line, '\"', j + 1) == 1)
	{
		while (line[++(*i)])
		{
			if (line[*i] == '\\' || line[*i + 1] == '\"' || line[*i + 1] == '$' || line[*i + 1] == '\\')
				line = slesh_parse(line, i);
			if (line[*i] == '\"')
				break ;
		}
		tmp = ft_substr(line, 0, j);
		tmp2 = ft_substr(line, j+ 1,  *i -j - 1);
		tmp3 = ft_strdup(line + *i + 1);
		tmp = ft_strjoin(tmp, tmp2);
		tmp = ft_strjoin(tmp, tmp3);
		(*i)--;
	}
	else
		return (line);
	// free(line);
	return (tmp);
}


int if_key(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

char *parse_dollar(char *line, int *i, char **get_env)
{
	int j = *i;
	char *tmp;
	char *tmp2;
	char *tmp3;
	char *tmp4;
	char *res;
	int z;

	while (line[++(*i)])
		if (!if_key(line[*i]))
			break ;
	if (*i == j + 1)
		return (line);
	tmp = ft_substr(line, j + 1, *i - j - 1);
	int k = -1;
	while (get_env[++k])
	{
		z = 0;
		while (get_env[k][z] && get_env[k][z] != '=')
			z++;
		tmp2 = ft_substr(get_env[k], 0, z);
		if (ft_strcmp(tmp, tmp2) == 0)
			break ;
	}
	tmp2 = ft_substr(get_env[k], z + 1, ft_strlen(get_env[k]) - z);
	tmp3 = ft_substr(line, 0, j);
	tmp4 = ft_substr(line, *i, ft_strlen(line));
	res = ft_strjoin(tmp3, tmp2);
	res = ft_strjoin(res, tmp4);
	return (res);
} 

char *parsing(char *line, char **get_env)
{
	t_ast *tmp;
	int i;

	i = -1;
	while (line[++i])
	{
			if (line[i] == '\'')
				line = single_quote_parse(line, &i);
			if (line[i] == '\\')
				line = slesh_parse(line, &i);
			if (line[i] == '\"')
				line = double_quote_parse(line, &i);
			if (line[i] == '$')
				line = parse_dollar(line, &i, get_env);
	}
	return (line);
}


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
		line = ft_strdup("echo \"\\hello\"");
		line = parsing(line, get_env);
		printf("%s\n", line);
	// }

}