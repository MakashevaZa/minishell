#include "minishell.h"

int	if_key(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

char	*parse_dollar(char *line, int *i, char **get_env, t_ast **ast)
{
	int j = *i;
	char *tmp;
	char *tmp1;
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
	tmp1 = ft_substr(get_env[k], z, ft_strlen(get_env[k]) - z);
	printf("tmp1 || = |%s|\n", tmp1);
	// tmp3 = ft_substr(line, 0, j);
	// printf("tmp3 = |%s|\n", tmp3);
	tmp4 = ft_substr(line, *i + 1, ft_strlen(line));
	printf("tmp4 = |%s|\n", tmp4);
	// res = ft_strjoin(tmp1, tmp4);
	// printf("res = %s\n", res);
	// res = ft_strjoin(res, tmp4);
	if (*ast == NULL)
			*ast = create_first_node(tmp);
		else
			add_value(ast, tmp);
	return (tmp4);
} 