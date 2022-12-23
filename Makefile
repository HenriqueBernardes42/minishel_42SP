CC				=	cc

CFLAGS			=	-I. \
					-Wall -Werror -Wextra

CDEPS			=	minishell.h

NAME			=	minishell

SRC_DIR			=	src

SRC				=	$(SRC_DIR)/assert.c \
					$(SRC_DIR)/ft_parse.c \
					$(SRC_DIR)/path.c \
					$(SRC_DIR)/throw.c \
					main.c

OBJ				= 	$(SRC:.c=.o)


LIBFT_DIR		= 	libft

RDL_DIR			=	/Users/katchogl/homebrew/Cellar/readline/8.2.1/lib

LIBS			=	$(LIBFT_DIR)/libft.a -L$(RDL_DIR) -lreadline

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(NAME)

$(LIBS):
	make -C $(LIBFT_DIR)

$(NAME): $(LIBS) $(OBJ)
	$(CC) $(LIBS) $(OBJ) -o $(NAME)

readline:
	brew install readline
	
clean:
	rm -f *.o */*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re readline