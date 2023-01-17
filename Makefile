CC				=	cc

CFLAGS			=	-I. -I$(READLINE)/include \
					-Wall -Werror -Wextra -g

CDEPS			=	minishell.h

NAME			=	minishell

SRC				=	main init destroy ft_execute assert \
					ft_redirect ft_heredocs error builtins \
					builtins2 signal ft_minishell_split \
					ft_isvalid ft_parse init2 ft_child \
					utils_builtins utils_execute \
					utils_libft_impl utils_minishell_split \
					utils utils2 utils_assert ft_expand

OBJ				=	$(patsubst %.c, src/%.o, $(SRC:=.c))

LIBFT_REPO		=	libft

LIBFT			=	$(LIBFT_REPO)/libft.a

READLINE		=	/Users/$(USER)/homebrew/opt/readline

%.o: %.c $(CDEPS)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT):
	git clone https://github.com/AtchogloDev/$(LIBFT_REPO).git
	make -C $(LIBFT_REPO)

$(READLINE)/lib:
	brew install readline

$(NAME): $(LIBFT) $(READLINE)/lib $(OBJ)
	$(CC) $(CFLAGS) $(LIBFT) -L$(READLINE)/lib -lreadline $(OBJ) -o $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

purge: fclean
	@rm -rf $(LIBFT_REPO)
	@rm -rf $(NAME).dsYM
	@rm -f $(NAME).log
	@rm -rf .vscode

uninstall:
	@if [[ -d $(READLINE) ]] ; \
	then \
		brew uninstall readline ; \
	fi ;

m: $(NAME)
	@./$(NAME)

mc: $(NAME)
	make && make clean && clear && ./$(NAME)

test-leaks: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

log-leaks: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all \
	--log-file=$(NAME).log ./$(NAME)

.PHONY: all clean fclean re purge m test-leaks log-leaks
