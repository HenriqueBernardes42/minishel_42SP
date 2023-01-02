CC				=	cc

CFLAGS			=	-I. -Wall -Werror -Wextra

CDEPS			=	minishell.h

NAME			=	minishell

SRC_FILES		=	assert ft_exec ft_parse init path throw main

SRC				=	$(patsubst %.c, src/%.o, $(SRC_FILES:=.c))

OBJ				= 	$(SRC:.c=.o)

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

uclean: fclean
	rm -rf libft
	@if [[ -d $(LIBREADLINE) ]] ; \
	then \
		brew uninstall readline ; \
	fi ; \

re: fclean all

.PHONY: all clean fclean uclean re
