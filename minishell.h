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

//-------ast.c
// t_ast*	create_node(char *value);

//------parsing.c------//

char	*parsing(char *line, char **get_env);
char	*single_quote_parse(char *line, int *i);
int		check_char(char *line, char ch, int i);
char	*double_quote_parse(char *line, int *i, char **get_env);
char	*slash_parse(char *line, int *i);

//------dollar_parse.c------//
char	*parse_dollar(char *line, int *i, char **get_env);
int		if_key(char c);


//------create_list.c------//
t_cmd  *new_list(char *arg);
void	add_back(t_cmd *lst, char *value);


t_ast*	insert_val(t_ast **ast, char *value);
 int check_arg(char *arg);
 void print_tree_rec(t_ast *ast, int level);
 t_ast*	create_node(char *value);
 void	add_value(t_ast **ast, char *value);
 
#endif