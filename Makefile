NAME = minishell

CC = gcc 
FLAGS = -Wall  -Wextra -L/Users/heveline/.brew/opt/readline/lib -I/Users/heveline/.brew/opt/readline/include

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)include/

HEADER =	minishell.h

SOURCES =	main.c\
			ast.c\
			builtins.c\
			dollar_parse.c\
			env_functions.c\
			go_through_tree.c\
			parsingAstArray.c\
			utils.c


OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER) 
	@make -C $(LIBFT_DIRECTORY)
	@$(CC) $(FLAGS) $(OBJECTS) -L. libft/libft.a -o $(NAME) -lreadline
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADER)
	@mkdir -p $(OBJECTS_DIRECTORY)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

test:	all
		./minishell


clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all