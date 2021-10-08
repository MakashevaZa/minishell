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

enum built_in {
	echo,
	cd,
	pwd,
	export,
	unset,
	env,
	// exit,
};

int check_arg(char *arg)
{
	int i = 0;

	if (ft_strcmp("echo", arg) == 0 || ft_strcmp("cd", arg) == 0
		|| ft_strcmp("pwd", arg) == 0 || ft_strcmp("export", arg) == 0
		|| ft_strcmp("unset", arg) == 0 || ft_strcmp("env", arg) == 0
		|| ft_strcmp("exit", arg) == 0)
		{
			// ast = create_node;
			return (1);
		}
	return (0);
}

void get_args(char *line)
{
	int i;
	char *arg;
	t_ast *ast;

	i = -1;
	while(line[++i])
	{
		if (line[i] == ' ')
		{
			arg = ft_substr(line, 0, i);
			if (check_arg(arg) == 1)
				ast = create_node(arg);
			printf("arg = %s\n", arg);
			printf("%s\n", ast->value);
			line = ft_strdup(line + i + 1);
			printf("line = %s\n", line);
			i = 0;
		}
		else
			i++;
	}
}

void *dfa(char *line)
{}

int main(int argc, char **argv, char **envp)
{
	char **get_env;
	char *line;
	// t_ast *ast;

	get_env = get_envp(envp);
	while (1)
	{
		// ast = create_node(ast);
		line = readline("> ");
		// line = ft_strdup("echo_____hey_____hey");
		// pre_parse(line);
		line = parsing(line, get_env);
		// dfa(line);
		get_args(line);
		printf("%s\n", line);
	}

}