#include "minishell.h"

int	check_char(char *line, char ch, int i)
{
	while (line[i])
	{
		if (line[i] == ch)
			return (1);
		(i)++;
	}
	return (0);
}

char	*slash_parse(char *line, int *i)
{
	char *tmp;
	char *tmp2;

	tmp = ft_substr(line, 0, *i);
	tmp2 = ft_strdup(line + *i);
	tmp = ft_strjoin(tmp, tmp2);
	// free(line);
	// ++(*i);
	return (tmp);
}

char *single_quote_parse(char *line, int *i, t_ast **ast)
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
		tmp = ft_strjoin(tmp, tmp2);
		tmp3 = ft_strdup(line + *i + 1);
		tmp3 = ft_strjoin(tmp, tmp3);
		return (tmp3);
	}
	return (line);
}

char	*double_quote_parse(char *line, int *i, char **get_env, t_ast **ast)
{
	int j = *i;
	char *tmp;
	char *tmp2;
	char *tmp3;

	if (check_char(line, '\"', j + 1) == 1)
	{
		while (line[++(*i)])
		{
			if (line[*i] == '\\' && (line[*i + 1] == '\"' || line[*i + 1] == '$' || line[*i + 1] == '\\'))
				line = slash_parse(line, i);
			if (line[*i] == '$')
				line = parse_dollar(line, i, get_env, ast);
			if (line[*i] == '\"')
				break ;
		}
		tmp = ft_substr(line, 0, j);
		printf("tmp = %s\n", tmp);
		tmp2 = ft_substr(line, j+ 1,  *i -j - 1);
		printf("tmp2 = %s\n", tmp2);
		tmp3 = ft_strdup(line + *i + 1);
		printf("tmp3 = %s\n", tmp3);
		tmp = ft_strjoin(tmp, tmp2);
		tmp = ft_strjoin(tmp, tmp3);
	}
	return (tmp);
}

char *skip_space(char *line, int *i,  t_ast **ast, char **get_env)
{
	int j = *i;
	char *tmp;
	char *tmp1;
	char *res;
	int k = -1;

	while (line[j] == ' ')
		j++;
	tmp = ft_substr(line, 0, *i);
	tmp1 = ft_substr(line, j, ft_strlen(line));
	while (tmp1[++k])
	{
		if (tmp1[k] == '\'')
			tmp1 = single_quote_parse(tmp1, &k, ast);
		if (tmp1[k] == '\"')
			tmp1 = double_quote_parse(tmp1, &k, get_env, ast);
		if (tmp1[k] == '$')
			tmp1 = parse_dollar(tmp1, &k, get_env, ast);
		if (tmp1[k] == '\\')
			tmp1 = slash_parse(tmp1, &k);
	}
	if (tmp1[ft_strlen(tmp1) - 1] == ' ')
		tmp1 = ft_substr(tmp1, 0, ft_strlen(tmp1) - 1);
	if (*ast == NULL)
		*ast = create_first_node(tmp1, tmp);
	else
		add_value(ast, tmp1);
	// printf("tmp1 = %s\n", tmp1);
	return (tmp1);
}

char *redirect_parse(char *line, t_ast **ast, int *i, char **get_env)
{
	int j = *i;
	int k = -1;
	char *tmp;
	char *tmp1;

	tmp = ft_substr(line, 0, j);
	while(tmp[++k])
	{
		if (tmp[k] == '\"')
			tmp = double_quote_parse(tmp, &k, get_env, ast);
		if (tmp[k] == '\'')
			tmp = single_quote_parse(tmp, &k, ast);
		if (tmp[k] == '$')
			tmp = parse_dollar(tmp, &k, get_env, ast);
		if (tmp[k] == '\\')
			tmp = slash_parse(tmp, &k);
		if (tmp[k] == ' ')
		{
			tmp = skip_space(tmp, &k, ast, get_env);
			break ;
		}
	}
	if (tmp[k] == '\0')
		add_value(ast, tmp);
	line = ft_strdup(line + j);
	j = 0;
	if (line[j + 1] == '>' || line[j + 1] == '<')
	{
		add_value(ast, ft_substr(line, 0, j + 2));
		line = ft_strdup(line + j + 2);
	}
	else
	{
		add_value(ast, ft_substr(line, 0, j + 1));
		line = ft_strdup(line + j + 1);
	}
	return (line);

}



t_ast	*parsing(char *line, char **get_env)
{
	int i;
	int j = -1;
	t_ast *ast;
	char *tmp;
	char **array;
	
	i = -1;
	ast = NULL;

	while (line[++i])
	{
		if (line[i] == '>' || line[i] == '<' || line[i] == '|'){
			// printf("line1 = %s\n", line);
			// array = array_init(line, &i);
			line = redirect_parse(line, &ast, &i, get_env);
			// printf("line = %s\n", line);
			i = -1;
		}
	}
	i = 0;
	if (line[i] == ' ')
		line = ft_substr(line, 1, ft_strlen(line) - 1);
	if (ast == NULL)
	{
		i = -1;
		while (line[++i])
		{
			if (line[i] == '\"')
				line = double_quote_parse(line, &i, get_env, &ast);
			if (line[i] == '\'')
				line = single_quote_parse(line, &i, &ast);
			if (line[i] == '$')
				line = parse_dollar(line, &i, get_env, &ast);
			if (line[i] == '\\')
				line = slash_parse(tmp, &i);
			if (line[i] == ' ')
				line = skip_space(line, &i, &ast, get_env);
		}
		if (ast == NULL)
			ast = create_node(line);
	}
	else
		add_value(&ast, line);
	return (ast);
}

