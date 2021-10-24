#include "minishell.h"

char *skip_space(char *line, int *i, t_ast *ast)
{
	int j = *i;
	char *tmp;
	char *tmp1;
	// char *res;
	// int k = -1;

	while (line[j] == ' ')
		j++;
	tmp = ft_substr(line, 0, *i);
	printf("tmp = %s\n", tmp);
	if (ast == NULL)
		ast = create_node(tmp);
	tmp1 = ft_substr(line, j, ft_strlen(line));
	printf("tmp1 = %s\n", tmp1);
	tmp1 = ft_strjoin(tmp, tmp1);
	return (tmp1);
}

char *redirect_parse(char *line, t_ast **ast, int *i, char **envp)
{
	int j = *i;
	int		k;
	char	*tmp;
	int		l;

	l = 0;
	k = -1;
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
		// if (tmp[k] == '\"')
		// 	tmp = double_quote_parse(tmp, &k, envp);
		// if (tmp[k] == '\'')
		// 	tmp = single_quote_parse(tmp, &k);
		// if (tmp[k] == '$')
		// 	tmp = parse_dollar(tmp, &k, envp);
		// if (tmp[k] == '\\')
		// 	tmp = slash_parse(tmp, &k);
		if (tmp[k] == ' ')
			tmp = skip_space(tmp, &k, ast);
	}
}

t_ast *parsing(char *line, char **envp)
{
	int		i;
	t_ast	*ast;

	i = -1;
	ast = NULL;
	while (line[++i])
	{
		if (line[i] == '>' || line[i] == '<' || line[i] == '|'){
			line = redirect_parse(line, &ast, &i, envp);
			i = -1;
		}
	}
}