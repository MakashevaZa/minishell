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

int skip_space(char *line, int *i)
{
	// int i = 0;
	while (line[*i] == ' ')
		(*i)++;
	return (*i);
}

// char *skip_space(char *line, int *i, t_cmd *list)
// {
// 	int j = *i;
// 	char *tmp;
// 	char *tmp1;
// 	char *res;

// 	while (line[j] == ' ')
// 		j++;
// 	tmp = ft_substr(line, 0, *i);
// 	if (list == NULL)
// 		list = new_list(tmp);
// 	else
// 		add_back(list, tmp);
// 	// printf("tmp = |%s|\n", tmp);
// 	tmp1 = ft_substr(line, j, ft_strlen(line));
// 	// printf("tmp1 = |%s|\n", tmp1);
// 	res = ft_strjoin(tmp, tmp1);
// 	return (tmp1);
// }

char	*parsing(char *line, char **get_env)
{
	int i;
	t_cmd *list = NULL;
	// int k = 0;
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
			{
				// k = skip_space(line);
				if (list == NULL)
					list = new_list(ft_substr(line, 0, i));
				else
					add_back(list, ft_substr(line, 0, i));
				line = ft_substr(line, skip_space(line, &i), ft_strlen(line));
				i = -1;
			}
	}
	add_back(list, line);
			// printf("list = %s\n", list->args[0]);
			while (list != NULL)
		{
			printf("value = |%s| prior = |%d|\n", list->value, list->prior);
			list = list->next;
		}
	return (line);
}
