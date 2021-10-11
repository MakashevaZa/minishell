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

char	*single_quote_parse(char *line, int *i)
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
		// printf("tmp = %s|\n", tmp);
		tmp2 = ft_substr(line, j + 1,  *i - j - 1);
		// printf("tmp2 = %s|\n", tmp2);
		tmp3 = ft_strdup(line + *i + 1);
		// printf("tmp3 = %s|\n", tmp3);

		tmp = ft_strjoin(tmp, tmp2);
		tmp = ft_strjoin(tmp, tmp3);
		(*i)--;
	}
	else
		return (line);
	return (tmp);
}

char	*double_quote_parse(char *line, int *i, char **get_env)
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
				line = parse_dollar(line, i, get_env);
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
	return (tmp);
}

char	*slash_parse(char *line, int *i)
{
	char *tmp;
	char *tmp2;

	tmp = ft_substr(line, 0, *i);
	tmp2 = ft_strdup(line + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	free(line);
	++(*i);
	return (tmp);
}
char *skip_space(char *line, int *i)
{
	int j = *i;
	char *tmp;
	char *tmp1;
	char *res;

	while (line[j] == ' ')
		j++;
	tmp = ft_substr(line, 0, *i + 1);
	tmp1 = ft_substr(line, j, ft_strlen(line));
	res = ft_strjoin(tmp, tmp1);
	return (res);
}

char	*parsing(char *line, char **get_env, t_cmd *list)
{
	int i;

	i = -1;
	while (line[++i])
	{
			if (line[i] == '\'')
				line = single_quote_parse(line, &i);
			if (line[i] == '\\')
				line = slash_parse(line, &i);
			if (line[i] == '\"')
				line = double_quote_parse(line, &i, get_env);
			if (line[i] == '$')
				line = parse_dollar(line, &i, get_env);
			if (line[i] == ' ')
				line = skip_space(line, &i);
	}
			// printf("list = %s\n", list->args[0]);
	return (line);
}
