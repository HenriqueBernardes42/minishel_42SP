CC				=	cc

CFLAGS			=	-I. -Wall -Werror -Wextra -g

CDEPS			=	minishell.h

NAME			=	minishell

SRC				=	main tools utils destroy init

OBJ				=	$(patsubst %.c, src/%.o, $(SRC:=.c))

LIBFT			=	libft/libft.a

42LOGIN			=	katchogl

LIBREADLINE		= 	/Users/$(42LOGIN)/homebrew/Cellar/readline/8.2.1/lib

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT):
	git clone https://github.com/AtchogloDev/libft.git
	make -C libft

$(LIBREADLINE):
	brew install readline

$(NAME): $(LIBFT) $(LIBREADLINE) $(OBJ)
	$(CC) $(CFLAGS) $(LIBFT) -L$(LIBREADLINE) -lreadline $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

reset: fclean
	rm -rf libft
	rm -rf minishell.dsYM
	rm -f minishell.log
	@if [[ -d $(LIBREADLINE) ]] ; \
	then \
		brew uninstall readline ; \
	fi ; \

m:
	./minishell

m-leaks:
	valgrind --leak-check=full --show-leak-kinds=all \
	--log-file=minishell.log ./minishell

.PHONY: all clean fclean re reset m m-leaks
