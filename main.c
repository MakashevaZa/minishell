#include "minishell.h"

void ft_err(char *str)
{
  ft_putendl_fd(str, 2);
  exit(1);
}

void free_array(char **str)
{
  int i;

  i = 0; 
	while (str[i])
		free(str[i++]);
	free(str[i]);
	free(str);
}

int	ft_strequal(const char *str1, const char *str2)
{
	while ((*str1 == *str2) && *str1 && *str2)
	{	
		str1++;
		str2++;
	}
  return (!((unsigned char)*str1 - (unsigned char)*str2));
}

size_t	ft_arraylen(char **str)
{
	size_t	n;

	n = 0;
	while (*str++)
		n++;
	return (n);
}

char	*path_handler(char *cmd, char **env)
{
	int		i;
	char	**path_list;
	char	*temp;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		ft_err("Error: problem with ENV, no PATHs found");
	path_list = ft_split(env[i] + 5, ':');
	i = 0;
	while (path_list[i])
	{
		path_list[i] = ft_strjoin(path_list[i], "/");
		temp = ft_strjoin(path_list[i], cmd);
		if (access(temp, F_OK) == 0)
			return (temp);
		i++;
	}
	ft_err("Error: no binary found for the command");
	return (NULL);
}

char **env_array(t_env **env_list)
{
  int i;
  t_env *tmp;
  char **array;
  char *equal;

  i = 0; 
  tmp = *env_list; 
  while (tmp)
  {
    i++;
    tmp = tmp->next;
  }
  array = (char **)malloc(sizeof(char *) * i);
  if (!array)
    return (NULL);
  tmp = *env_list;
  while (tmp)
  {
    equal = ft_strjoin(tmp->key, "="); //protect
    *array = ft_strjoin(equal, tmp->value); //protect and clean what was created
    array++;
    tmp = tmp->next;
    free(equal);
  }
  *array = NULL;
  return array;
}

void  binary_command(char **cmd_array, t_env **env_list)
{
  char **env;
  char *path;

  env = env_array(env_list);
  path = path_handler(cmd_array[0], env);
  execve(path, cmd_array, env);
  
}

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
/*
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
*/
// void	handlerInt(int signum)
// {
// 	signum = 0;
// 	rl_on_new_line();
// 	rl_redisplay();
// 	write(1, "  \b\b\n", 5);
// 	rl_on_new_line();
// 	rl_replace_line("", 1);
// 	rl_redisplay();
// 	exit(1);
// }

// void	sigHandler(void)
// {
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGINT, handlerInt);
// }
/*
char *start_loop(void)
{
	sigHandler();
	return (readline("Z&D_Shell > "));
}
*/
// void	handlerIntHD(int signum)
// {
// 	signum = 0;
// 	rl_on_new_line();
// 	rl_redisplay();
// 	write(1, "  \b\b\n", 5);
// 	exit(1);
// }

// void	sigHDHandle(void)
// {
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGINT, handlerIntHD);
// }

t_data	*create_data(char **envp)
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

    (void)argc;
    (void)argv;
	data = create_data(envp);
	// while (1)
	// {
	// 	line = readline("Z&D_Shell > ");
	// 	sigHandler();
		line = ft_strdup("echo  \'     \'   hey > a");
		
		// if (!line)
		// {
		// 	ft_putendl_fd("exit", STDOUT_FILENO);
		// 	break ;
		// }
		// if (line[0] == '\0')
		// {
		// 	free(line);
		// 	continue;
		// }
        // add_history(line);
		/*array = array_init(line); //?
		if (!array)
			continue ;*/
		// pid = fork();
		array = parsing(line, envp);
		int i = -1;
		while (array[++i])
			printf("%s\n", array[i]);
		// signal(SIGINT, SIG_IGN);
		// if (pid == 0)
		// {
		// 	sigHDHandle();
		// 	// ast = parsing(line, envp); 
	    //     go_through_tree(ast, data);

		// 	exit (0);
		// }
		// waitpid(pid, NULL, 0);
        
		// printf("%s\n", line);
	// }
    // clear_history();
    return EXIT_SUCCESS;
		
}