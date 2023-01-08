CC				=	cc

CFLAGS			=	-I. -I/Users/$(USER)/.brew/opt/readline/include \
					-Wall -Werror -Wextra -g

CDEPS			=	minishell.h

NAME			=	minishell

SRC				=	main init destroy utils ft_execute assert \
					ft_redirect ft_heredocs error builtins \
					builtins2 signal utils2

OBJ				=	$(patsubst %.c, src/%.o, $(SRC:=.c))

LIBFT_REPO		=	libft

LIBFT			=	$(LIBFT_REPO)/libft.a

LIBREADLINE		= 	/Users/$(USER)/.brew/opt/readline/lib

%.o: %.c $(CDEPS)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT):
	git clone https://github.com/AtchogloDev/$(LIBFT_REPO).git
	make -C $(LIBFT_REPO)

$(LIBREADLINE):
	brew install readline

$(NAME): $(LIBFT) $(LIBREADLINE) $(OBJ)
	$(CC) $(CFLAGS) $(LIBFT) -L$(LIBREADLINE) -lreadline $(OBJ) -o $(NAME)

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
	@if [[ -d $(LIBREADLINE) ]] ; \
	then \
		brew uninstall readline ; \
	fi ;

m: $(NAME)
	@./$(NAME)

test-leaks: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

log-leaks: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all \
	--log-file=$(NAME).log ./$(NAME)

.PHONY: all clean fclean re purge m test-leaks log-leaks
