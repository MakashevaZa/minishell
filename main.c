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

char *single_quote_parse(char *line, int *i)
{
	int j = *i;
	char *tmp;
	char *tmp2;
	char *tmp3;
	while (line[++(*i)])
	{
		if (line[*i] == '\'')
			break ;
	}
	tmp = ft_substr(line, 0, j);
	tmp2 = ft_substr(line, j+ 1,  *i -j - 1);
	tmp3 = ft_strdup(line + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	printf("tmp single = %s", tmp);
	return (tmp);
}

char	*double_quote_parse(char *line, int *i)
{
	int j = *i;
	char *tmp;
	char *tmp2;
	char *tmp3;

	while (line[++(*i)])
	{
		// if (line[*i] == '\\' || line[*i + 1] == '\"' || line[*i + 1] == '$' || line[*i + 1] == '\\') \\dont understand this case
		// 	line = ft_slesh(line, i);
		if (line[*i] == '\"')
			break ;
	}
	tmp = ft_substr(line, 0, j);
	tmp2 = ft_substr(line, j+ 1,  *i -j - 1);
	tmp3 = ft_strdup(line + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	printf("tmp double = %s", tmp);
	free(line);
	return (tmp);
}

char	*slesh_parse(char *line, int *i)
{
	int j = *i;
	char *tmp;
	char *tmp2;
	char *tmp3;

	tmp = ft_substr(line, 0, j);
	tmp2 = ft_substr(line, j+ 1,  *i -j - 1);
	tmp3 = ft_strdup(line + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	printf("tmp double = %s", tmp);
	free(line);
	++(*i);
	return (tmp);
}

void parsing(char *line)
{
	t_ast *tmp;
	int i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'')
		{
			line = single_quote_parse(line, &i);
			// i--;
		}
		if (line[i] == '\\')
			line = slesh_parse(line, &i);
		if (line[i] == '\"')
			line = double_quote_parse(line, &i);
		i++;
	}
}

int main(int argc, char **argv, char **envp)
{
	char **get_env;
	char *line;
	// t_ast *ast;
	// static int i;

	get_env = get_envp(envp);
	// while (1)
	// {
		// ast = create_ast(ast);
		// line = readline("> ");
		line = ft_strdup("comma'nnn'da'00000000'lol");
		parsing(line);
	// }

}