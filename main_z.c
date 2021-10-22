#include "minishell.h"


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

int main(int argc, char **argv, char **env)
{
  // Load config files, if any.

  // Run command loop.
//  lsh_loop();

  // Perform any shutdown/cleanup.
  size_t a;
  char **cmd_array = argv;
  char *buf;
  t_env *env_list;


  a = argc;
  env_list = env_init(env);
  while ((buf = readline("Z&D_Shell > ")) != NULL) 
  {
    if (ft_strlen(buf) > 0) 
    {
      add_history(buf);
      cmd_array = ft_split(buf, ' '); //parser!!!!!!! as  "        " won't be a proper argument
    
      if (ft_strequal(cmd_array[0], "env"))
        env_builtin(env_list);
      else if (ft_strequal(cmd_array[0], "export"))
        export_builtin(cmd_array, &env_list);
      else if (ft_strequal(cmd_array[0], "unset"))
        unset_builtin(cmd_array, &env_list);
      else if (ft_strequal(cmd_array[0], "echo"))
        echo_builtin(cmd_array);
      else if (ft_strequal(cmd_array[0], "cd"))
        cd_builtin(cmd_array, &env_list);
      else if (ft_strequal(cmd_array[0], "exit"))
        exit_builtin();
      else if (ft_strequal(cmd_array[0], "pwd"))
        pwd_builtin();
      else
        binary_command(cmd_array, &env_list);
      free(buf);
      free_array(cmd_array); // do we need to clean this one? within corresponding func?
    }
  }
  free_env(env_list);
  clear_history();
  return EXIT_SUCCESS;
}

/*

export w+=er()%$#@!±
bash: !±: event not found

parser!!!!!!! as  "        " won't be a proper argument
*/