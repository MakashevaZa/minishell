#include "minishell.h"

void env_builtin(t_env *start)
{
    t_env *temp = start;

    while (temp != NULL)
    {
      if (temp->value)
      {
        ft_putstr_fd(temp->key, 1);
        ft_putchar_fd('=', 1);
        ft_putstr_fd(temp->value, 1);
        ft_putchar_fd('\n', 1);
      }
        temp = temp->next;
    }

}

void echo_builtin(char **cmd)
{
  int endl;
  int i;

  endl = 0;
  if (cmd[1] && ft_strequal(cmd[1], "-n"))
    endl = 1;
  i = 1 + endl;
  while (cmd[i])
  {
    ft_putstr_fd(cmd[i++], 1);
    if (cmd[i])
      ft_putchar_fd(' ', 1);
  }
  if (!endl)
    ft_putstr_fd("\n", 1);
}


void pwd_builtin()
{
  char *pwd;

  pwd = getcwd(NULL, 0);
  ft_putendl_fd(pwd, 1);
  free(pwd);
}

void unset_builtin(char **cmd_array, t_env **env_list)
{
  t_env *deleted;
  int i;

  i = 1;
  while (cmd_array[i])
  {
    if (unset_arg_isok(cmd_array[i]))
      {
        deleted = env_exists(env_list, cmd_array[i]);
        if (deleted)
          delete_env(deleted, env_list);
      }
    else
      printf("error with %s\n", cmd_array[i]);
    i++;
  }
}

void export_builtin(char **cmd_array, t_env **env_list)
{  
  t_env *export_list;

  export_list = NULL;
  if (ft_arraylen(cmd_array) == 1)
  {
    export_list = env_cpy(*env_list);
    bubbleSort(&export_list);
    print_export_list(export_list);
    free_env(export_list);
  }
  else
  {
    int i = 1;
    while (cmd_array[i])
    {
      if (export_pair_isok(cmd_array[i]))
        change_envlist(cmd_array[i], env_list); 
      else
        printf("Error: %s\n", cmd_array[i]);
      i++;
    }
  }
}

void exit_builtin()
{
  exit(0);
}


void cd_builtin(char **cmd, t_env **env_list)
{
  char *cwd;
  t_env *home;
  t_env *current;
  char *tempvalue;
  char *d[3];

  d[2] = NULL;
  cwd = getcwd(NULL, 0);
  if (cmd[1] == NULL)
  {
    home = env_exists(env_list, "HOME");
    if (home)
    {
      if (chdir(home->value) != 0)
        printf("Error while going to Home, cd with no args");
      else
      {
        current = env_exists(env_list, "OLDPWD");
        if (current)
        {
            tempvalue = current->value;
            current->value = cwd;
            free(tempvalue);
        }
        else
        {
          d[0] = "OLDPWD";
          d[1] = cwd;
          create_env_node(env_list, d);
          free(d);
        }
        current = env_exists(env_list, "PWD");
        if (current)
        {
            tempvalue = current->value;
            current->value = home->value;
            free(tempvalue);
        }
        else
        {
          d[0] = "PWD";
          d[1] = home->value;
          create_env_node(env_list, d);
          free(d);
        }
      }
    }
    else
      printf("No HOME path");
    free(home);
  }
  else
  {
    if (chdir(cmd[1]) != 0)
      printf("the path is incorrect");
    else
      {

        current = env_exists(env_list, "OLDPWD");
        if (current)
        {
            tempvalue = current->value;
            current->value = cwd;
            free(tempvalue);
        }
        else
        {
          d[0] = "OLDPWD";
          d[1] = cwd;
          create_env_node(env_list, d);
          free(d);
        }
        current = env_exists(env_list, "PWD");
        cwd = getcwd(NULL, 0);
        if (current)
        {
            tempvalue = current->value;
            current->value = cwd;
            free(tempvalue);
        }
        else
        {
          d[0] = "PWD";
          d[1] = cwd;
          create_env_node(env_list, d);
          free(d);
        }
      }

  }

  free(cwd);
}