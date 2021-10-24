#include "minishell.h"

// char **get_envp(char **envp)
// {
// 	char **data;
// 	int i;

// 	i = 0;
// 	while (envp[i])
// 		i++;
// 	data = (char **)malloc(sizeof(char *) * i + 1);
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
// 	// printf("%d\n", i);
// 	return(data);
// }

char **array_init(char *line)
{
	char **array;
	int j;
	int ind;
	char *tmp;
	int i = -1;

	ind = 0;
	j = 0;
	while (line[++i])
	{
		if (line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			tmp = ft_substr(line, 0, i);
			break ;
		}
	}
	tmp = ft_substr(line, 0, i);
	array = (char **)malloc(sizeof(char *) * ft_strlen(tmp));
	if (!array)
		return (NULL);
	while (tmp[j])
	{
		if (tmp[j] == ' ')
		{
			array[ind] = ft_substr(tmp, 0, j);
			tmp = ft_substr(tmp, j + 1, ft_strlen(tmp) - j);
			ind++;
			j = -1;
		}
		j++;
	}
	array[ind] = tmp;
	return (array);
}

void	handlerInt(int signum)
{
	signum = 0;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \b\b\n", 5);
	rl_on_new_line();
	// rl_replace_line("", 1);
	rl_redisplay();
	exit(1);
}

void	sigHandler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handlerInt);
}
char *start_loop(void)
{
	sigHandler();
	return (readline("Z&D_Shell > "));
}

void	handlerIntHD(int signum)
{
	signum = 0;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \b\b\n", 5);
	exit(1);
}

void	sigHDHandle(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handlerIntHD);
}

t_data	*create_data(char **envp, int argc, char **argv)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	data->env = env_init(envp);
	data->fd_in = dup(STDIN_FILENO); //need to change to dup2(int, int)
	data->fd_out = dup(STDOUT_FILENO); //same
	data->pid = 1;
	return (data);
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**array;
	t_data	*data;
	t_ast	*ast;
	int		pid;

	data = create_data(envp, argc, argv);
	while (1)
	{
		line = start_loop();
		// line = ft_strdup("cat main | wc > a");
		if (!line)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (line[0] == '\0')
		{
			free(line);
			continue;
		}
		array = array_init(line);
		if (!array)
			continue ;
		pid = fork();
		signal(SIGINT, SIG_IGN);
		if (pid == 0)
		{
			sigHDHandle();
			ast = parsing(line, envp); //do we need get_env? why not envp
			print_tree_rec(ast, 0);
			exit (0);
		}
		waitpid(pid, NULL, 0);
		// go_through_tree(ast, data);
		// printf("%s\n", line);
	}
}