#include "minishell.h"

char *skip_space(char *line, int *i)
{
	int j = *i;
	char *tmp;
	char *tmp1;

	while (line[j] == ' ')
		j++;
	tmp = ft_substr(line, 0, *i + 1);
	tmp1 = ft_substr(line, j, ft_strlen(line));
	tmp1 = ft_strjoin(tmp, tmp1);
	return (tmp1);
}

char *redirect_parse(char *line, int *i, char **envp)
{
	int j = *i;
	int		k;
	char	*tmp;
	int		l;
	int		c;

	l = 0;
	k = -1;
	c = 0;
	tmp = ft_substr(line, 0, j);
	if (tmp[l] == ' ')
	{
		while (tmp[l] == ' ')
			l++;
		tmp = ft_substr(line, l, j - l);
	}
	if (tmp[ft_strlen(tmp) - 1] == ' ')
		tmp = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
	while(tmp[++k])
	{
		if (tmp[k] == ' ')
			tmp = skip_space(tmp, &k);
	}
	line = ft_strdup(line + j);
	line = ft_strjoin(tmp, line);
	return (line);
}

int find_redir(char *line)
{
	int i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '>' || line[i] == '<' || line[i] == '|')
			break ;
	}
	return (i);
}

char **parsing(char *line, char **envp)
{
	int		i;
	char	**array;
	int		c;
	int redir;
	char	*tmp;

	i = -1;
	c = 0;
	array = (char **)malloc(sizeof(char *));
	if (!array)
		return (NULL);
	while (line[++i])
	{
		if (line[i] == '>' || line[i] == '<' || line[i] == '|'){
			line = redirect_parse(line, &i, envp);
			redir = find_redir(line);
			tmp = ft_substr(line, 0, redir);
			array[c++] = tmp;
			line = ft_substr(line, redir, ft_strlen(line) - redir);
			i = 0;
			if (line[i + 1] == '>' || line[i] == '<')
			{
				tmp = ft_substr(line, 0, i + 2);
				line = ft_strdup(line + i + 2);
			}
			if (line[i] == '>' || line[i] == '<' || line[i] == '|')
			{
				tmp = ft_substr(line, 0, i + 1);
				line = ft_strdup(line + i + 1);
			}
			array[c++] = tmp;
			i = -1;
		}
	}
	i = 0;
	if (line[i] == ' ')
		line = ft_substr(line, 1, ft_strlen(line) - 1);
	while (line[i++])
	{
		if (line[i] == ' ')
			line = skip_space(line, &i);
	}
	array[c++] = line;
	return (array);
}