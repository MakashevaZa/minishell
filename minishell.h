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


typedef struct s_data
{
	t_list	*env;
	int		pid;
	int		fd_out;
	int		fd_in;
	int		view;
}			t_data;


//-------ast.c
// t_ast*	create_node(char *value);

//------parsing.c------//

void	*parsing(char *line, char **get_env);
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
#endif