#ifndef MINISHELL
# define MINISHELL

#include "./libft/include/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <unistd.h>

typedef struct s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
	char			*value;
	char			*command;
	// char			**args;
	int				prior;
}					t_ast;


typedef struct s_cmd
{
	char			*value;
	int 			prior;
	// int				size;
	// int				pipe;
	// int				redir;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;


typedef struct s_env
{
  char          *key;
  char          *value;
  struct s_env  *next;
} t_env;

//-------ast.c
// t_ast*	create_node(char *value);

//------parsing.c------//

t_ast	*parsing(char *line, char **get_env);
// char	*parsing(char *line, char **get_env);
// char	*single_quote_parse(char *line, int *i);
int		check_char(char *line, char ch, int i);
// char	*double_quote_parse(char *line, int *i, char **get_env);
char	*slash_parse(char *line, int *i);

//------dollar_parse.c------//
char	*parse_dollar(char *line, int *i, char **get_env, t_ast **ast);
int		if_key(char c);


//------create_list.c------//
t_cmd  *new_list(char *arg);
void	add_back(t_cmd *lst, char *value);


t_ast*	insert_val(t_ast **ast, char *value);
 int check_arg(char *arg);
 void print_tree_rec(t_ast *ast, int level);
 t_ast*	create_node(char *value);
 t_ast*	create_first_node(char *value, char *command);
void	add_value(t_ast **ast, char *value); 
t_ast search(t_ast *ast);

/* -- builtins -- */

void env_builtin(t_env *start);
void echo_builtin(char **cmd);
void pwd_builtin();
void cd_builtin(char **cmd, t_env **env_list);
void exit_builtin();
void export_builtin(char **cmd_array, t_env **env_list);
void unset_builtin(char **cmd_array, t_env **env_list);

/* -- env funcs -- */

char	**ft_split_env(char const *s, char c);
void print_export_list(t_env *start);
void ft_swap(t_env **start, t_env *a, t_env *b);
void bubbleSort(t_env **start);
t_env	*ft_lastnode(t_env *lst);
int create_env_node(t_env **lst, char **d);
t_env *env_init(char **env);
t_env *env_cpy(t_env *head);
void free_env(t_env *head);
int export_pair_isok(char *pair);
t_env *env_exists(t_env **env_list, char *key);
void change_envlist(char *new_env, t_env **env_list);
void delete_env(t_env *deleted, t_env **env_list);
int unset_arg_isok(char *arg);

/* -- may be added to the lib -- */

int	ft_strequal(const char *str1, const char *str2);
size_t	ft_arraylen(char **str);
void free_array(char **str);

#endif