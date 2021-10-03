#include "minishell.h"

// char **get_envp(char **envp)
// {
// 	char **data;
// 	int i;

// 	i = 0;
// 	while (envp[i])
// 		i++;
// 	data = (char **)malloc(sizeof(char *) * (i + 1));
// 	if (!data)
// 	{
// 		write(1, "Error in memory allocation\n", ft_strlen("Error in memory allocation\n"));
// 		exit (1);
// 	}
// 	i = 0;
// 	while (envp[i])
// 	{
// 		data[i] = ft_strdup(envp[i]);
// 		i++;
// 	}
// 	data[i] = '\0';
// 	return(data);
// }

int redirection_pars(char *line, int i)

void parsing(char *line, t_ast *ast)
{
	t_ast *tmp;
	int i;

	i = -1;
	while (line[++i])
	{
		if (ft_strchr("><\'\"$", line[i]))
		{
			if (line[i] == '>' || line[i] == '<')
				redirection_pars(line, i);
		}
	}
}

int main(int argc, char **argv, char **envp)
{
	// char **get_env;
	char *line;
	t_ast *ast;

	// get_env = get_envp(envp);
	while (1)
	{
		ast = create_ast(ast);
		line = readline("> ");

	}

}