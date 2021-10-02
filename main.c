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
	data[i] = '\0';
	return(data);
}

int main(int argc, char **argv, char **envp)
{
	char **get_env;
	int i;
	char *line;

	get_env = get_envp(envp);
	get_next_line(0, &line);
	
}