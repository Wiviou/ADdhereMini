NAME	= minishell

CC		= cc
CFLAGS		= -Wall -Werror -Wextra 
INC_DIR		= inc/
SRC_DIR		= src/
OBJ_DIR		= obj/
LIBFT_DIR	= libft/

SRCS		= $(SRC_DIR)main.c \
		  $(SRC_DIR)exec.c \
		  $(SRC_DIR)exec1.c \
		  $(SRC_DIR)exec2.c \
		  $(SRC_DIR)exec3.c \
		  $(SRC_DIR)exec4.c \
		  $(SRC_DIR)gestion_d_list.c \
		  $(SRC_DIR)gestion_liste.c \
		  $(SRC_DIR)gestion_liste2.c \
		  $(SRC_DIR)token.c \
		  $(SRC_DIR)token2.c \
		  $(SRC_DIR)token3.c \
		  $(SRC_DIR)token4.c \
		  $(SRC_DIR)token5.c \
		  $(SRC_DIR)token6.c \
		  $(SRC_DIR)token_0.c \
		  $(SRC_DIR)token_02.c \
		  $(SRC_DIR)utils.c \
		  $(SRC_DIR)ft_split_quote.c \
		  $(SRC_DIR)ft_split_quote2.c \
		  $(SRC_DIR)clean_quote.c \
		  $(SRC_DIR)search_multi.c \
		  $(SRC_DIR)exec_now.c \
		  $(SRC_DIR)exec_now1.c \
		  $(SRC_DIR)exec_now2.c \
		  $(SRC_DIR)exec_now3.c \
		  $(SRC_DIR)envp.c \
		  $(SRC_DIR)liste_env.c \
		  $(SRC_DIR)liste_env2.c \
		  $(SRC_DIR)read_shell.c \
		  $(SRC_DIR)command_main.c \
		  $(SRC_DIR)build.c \
		  $(SRC_DIR)clean_concat.c \
		  $(SRC_DIR)heredoc.c \
		  $(SRC_DIR)heredoc2.c \
		  $(SRC_DIR)heredoc3.c \
		  $(SRC_DIR)heredoc4.c \
		  $(SRC_DIR)heredoc5.c \
		  $(SRC_DIR)replace_env_var.c \
		  $(SRC_DIR)exec_utils.c \
		  $(SRC_DIR)build_utils.c \
		  $(SRC_DIR)make_env.c \
		  $(SRC_DIR)make_env2.c \
		  $(SRC_DIR)read_shell1.c \
		  $(SRC_DIR)read_shell2.c \
		  $(SRC_DIR)read_shell3.c \
		  $(SRC_DIR)read_shell4.c \
		  $(SRC_DIR)read_shell5.c \
		  $(SRC_DIR)read_shell6.c \
		  $(SRC_DIR)read_shell7.c \
		  $(SRC_DIR)read_shell8.c \
		  $(SRC_DIR)read_shell9.c \
		  $(SRC_DIR)replace_env_var1.c \
		  $(SRC_DIR)replace_env_var2.c \
		  $(SRC_DIR)replace_env_var3.c \
		  $(SRC_DIR)utils2.c \
		  $(SRC_DIR)clean_concat1.c \
		  $(SRC_DIR)command_main1.c \
		  $(SRC_DIR)command_main2.c \
		  $(SRC_DIR)main1.c \
		  $(SRC_DIR)main2.c \
		  $(SRC_DIR)main3.c \
		  $(SRC_DIR)main4.c \
		  $(SRC_DIR)exec_utils2.c \
		  $(SRC_DIR)envp2.c \
		  $(SRC_DIR)envp3.c \
		  $(SRC_DIR)envp4.c \

OBJ		= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

INC		= -I$(INC_DIR) -I$(LIBFT_DIR)

LIBFT		= $(LIBFT_DIR)libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME) -lreadline

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY:	all clean fclean re
