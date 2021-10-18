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

char	*single_quote_parse(char *line, int *i, t_ast **ast)
{
	int j = *i;
	int k = 0;
	printf("line = |%s|\n", line);
	char *tmp;
	char *tmp2;
	char *tmp3;
	if (check_char(line, '\'', j + 1) == 1)
	{
		// while (line[j++] = ' ')
		// 	j++;
		while (line[++(*i)])
		{
			if (line[(*i)] == ' ')
				k++;
			if (line[(*i)] == '\'')
				break ;
		}
		printf("i = %d\n", *i);
		// tmp = ft_substr(line, j + 1, k);
		tmp = ft_substr(line, k + 1, *i - k -1);
		// printf("tmp = |%s|\n", tmp);
		// tmp2 = ft_substr(line, k + 1,  *i - j - 1);
		// printf("tmp2 = |%s|\n", tmp2);
		tmp3 = ft_strdup(line + *i + 1);
		// tmp = ft_strjoin(tmp, tmp2);
		if (*ast == NULL)
			*ast = create_first_node(tmp);
		else
			add_value(ast, tmp);
	}
	else
		exit(1);
	return (tmp3);
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
		// tmp = ft_substr(line, 0, j);
		// printf("tmp = |%s|\n", tmp);
		tmp2 = ft_substr(line, j+ 1,  *i -j - 1);
		// printf("tmp2 = |%s|\n", tmp2);
		tmp3 = ft_strdup(line + *i + 1);
		// printf("tmp3 = |%s|\n", tmp3);
		tmp = ft_strjoin(tmp, tmp2);
		// printf("tmp = |%s|\n", tmp);
		if (*ast == NULL)
			*ast = create_first_node(tmp);
		else
			add_value(ast, tmp);
	}
	else
		return (line);
	return (tmp3);
}

char	*slash_parse(char *line, int *i)
{
	char *tmp;
	char *tmp2;

	tmp = ft_substr(line, 0, *i);
	// printf("tmp = %s\n", tmp);
	tmp2 = ft_strdup(line + *i);
	// printf("tmp2 = %s\n", tmp2);
	tmp = ft_strjoin(tmp, tmp2);
	// printf("tmp = %s\n", tmp);
	// if (*ast == NULL)
	// 		*ast = create_first_node(tmp);
	// else
	// 	add_value(ast, tmp);
	free(line);
	++(*i);
	return (tmp);
}
char *skip_space(char *line, int *i, t_ast **ast)
{
	int j = *i;
	char *tmp;
	char *tmp1;
	char *res;

	while (line[j] == ' ')
		j++;
	tmp = ft_substr(line, 0, *i);
	// printf("tmp = |%s|\n", tmp);
	tmp1 = ft_substr(line, j, ft_strlen(line));
	if (*ast == NULL)
		*ast = create_first_node(tmp);
	else
		add_value(ast, tmp);
	// printf("tmp1 = |%s|\n", tmp1);
	// res = ft_strjoin(tmp, tmp1);
	return (tmp1);
}

t_ast	*parsing(char *line, char **get_env)
{
	int i;
	t_ast *ast;
	int index;

	ast = NULL;
	i = -1;
	index = 0;
	while (line[++i])
	{
			if (line[i] == '\''){
				line = single_quote_parse(line, &i, &ast);
				i = -1;
			}
			if (line[i] == '\\'){
				line = slash_parse(line, &i);
				// i = -1;
				}
			if (line[i] == '\"')
			{
				line = double_quote_parse(line, &i, get_env, &ast);
				printf("line = %s\n", line);
				i = -1;
			}
			if (line[i] == '$'){
				line = parse_dollar(line, &i, get_env, &ast);
				i = -1;
			}
			if (line[i] == ' '){
				line = skip_space(line, &i, &ast);
				i = -1;}
	}
	if (ast == NULL)
		ast = create_first_node(line);
	else
		add_value(&ast, line);
			// printf("list = %s\n", list->args[0]);
	return (ast);
}

// char	*parsing(char *line, char **get_env)
// {
// 	int i;

// 	i = -1;
// 	while (line[++i])
// 	{
// 			if (line[i] == '\'')
// 				line = single_quote_parse(line, &i);
// 			if (line[i] == '\\')
// 				line = slash_parse(line, &i);
// 			if (line[i] == '\"')
// 				line = double_quote_parse(line, &i, get_env);
// 			if (line[i] == '$')
// 				line = parse_dollar(line, &i, get_env);
// 			if (line[i] == ' ')
// 				line = skip_space(line, &i);
// 	}
// 			// printf("list = %s\n", list->args[0]);
// 	return (line);
// }
