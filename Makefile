.PHONY: all clean fclean re cleanb fcleanb reb

CC			=	gcc
CFLAGS		=	-g -Wall -Wextra -Werror -fPIE
RL_FLAG		=	-lreadline

SUPP_FILES	=	readline.supp add_history.supp
SUPP_PRFX	=	--suppressions=./supps
SUPP_SRC	=	$(addprefix $(SUPP_PRFX)/, $(SUPP_FILES))
VALGRIND	=	valgrind --track-origins=yes --leak-check=full \
				--show-leak-kinds=all
VALGRIND	+=	$(SUPP_SRC)

LIBFT		=	libft/libft.a

NAME		=	minishell
SRC_DIR		=	src
OBJ_DIR		=	objects
HEADER		=	$(SRC_DIR)/minishell.h


SRC_FILES	+=      main.c init.c destroy.c ft_execute.c assert.c \
					ft_redirect.c heredocs.c error.c builtins.c \
					builtins2.c signal.c ft_minishell_split.c \
					ft_isvalid.c ft_parse.c init2.c ft_child.c \
					utils_builtins.c utils_execute.c \
					utils_minishell_split.c \
					utils_tab.c utils.c utils_assert.c expand.c \
					utils_child.c utils_expand.c utils_history.c \
					ft_isfinished.c ft_explode_env.c utils2.c \
					signal2.c quotes.c


SRC			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ			=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@printf "\n$(BLUE_BACK) creating object %s  ...$(RE)\n" $@
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_B)/%.o: $(SRC_DIR_B)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(HEADER)
	@printf "\n$(CY) creating lib %s  ...$(RE)\n" $@
	@make -C ./libft
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(RL_FLAG)
	@printf "\n$(CY) Done! $(RE)\n" $@


$(OBJ_DIR):
	@printf "\n$(BLUE_BACK) Criando diretorios ... $(RE)\n"
	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(OBJ_DIR)/builtins

clean:
	@printf "\n$(RED_BACk) cleaning object files ... $(RE)\n"
	@rm -rf objects objects_bonus

fclean: clean
	@printf "\n$(RED_BACk) cleaning lib ... $(RE)\n"
	@find -name '$(NAME)' -delete

re:
	@make fclean && make all

test: all
	./$(NAME) $(TEST_LIST)

val: all
	$(VALGRIND) ./$(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_DIR_B) $(OBJ_BONUS) $(HEADER_B)
	@make -C ./libft
	@$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS) $(LIBFT)

$(OBJ_DIR_B):
	@mkdir -p $(OBJ_DIR_B)/utils
	@mkdir -p $(OBJ_DIR_B)/operations

cleanb:
	@rm -rf $(OBJ_DIR_B)

fcleanb:
	@make cleanb
	@find -name '$(NAME_BONUS)' -delete

reb:
	@make fcleanb && make $(NAME_BONUS)

testb: $(NAME) $(NAME_BONUS)
	./$(NAME) $(TEST_LIST) | ./$(NAME_BONUS) $(TEST_LIST)


RE	= \033[0m
BLUE_BACK	= \033[1m\033[44m
RED_BACk	= \033[1m\033[41m
CY	= \033[36;1m
RC	= \033[0m