NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

OBJ_FILES = \
	obj/ft_memset.o \
	obj/ft_bzero.o \
	obj/ft_memcpy.o \
	obj/ft_memmove.o \
	obj/ft_memchr.o \
	obj/ft_memcmp.o \
	obj/ft_strlen.o \
	obj/ft_strlcpy.o \
	obj/ft_strlcat.o \
	obj/ft_strchr.o \
	obj/ft_strrchr.o \
	obj/ft_strnstr.o \
	obj/ft_strncmp.o \
	obj/ft_atoi.o \
	obj/ft_isalpha.o \
	obj/ft_isdigit.o \
	obj/ft_isalnum.o \
	obj/ft_isascii.o \
	obj/ft_isprint.o \
	obj/ft_toupper.o \
	obj/ft_tolower.o \
	obj/ft_calloc.o \
	obj/ft_strdup.o \
	obj/ft_substr.o \
	obj/ft_strjoin.o \
	obj/ft_strtrim.o \
	obj/ft_split.o \
	obj/ft_itoa.o \
	obj/ft_strmapi.o \
	obj/ft_striteri.o \
	obj/ft_putchar_fd.o \
	obj/ft_putstr_fd.o \
	obj/ft_putendl_fd.o \
	obj/ft_putnbr_fd.o \
	obj/ft_dlstnew.o \
	obj/ft_dlstadd_back.o \
	obj/ft_strjoin2.o \
	obj/ft_dlstclear.o \
	obj/ft_printf.o \
	obj/ft_dlstdelone.o \
	obj/ft_dlstiter.o \
	obj/ft_atol.o \
	obj/ft_dlstlast.o \
	obj/ft_isspace.o \
	obj/ft_resolve_flg.o \
	obj/ft_resolve_str.o \
	obj/ft_resolve_dec.o \
	obj/ft_resolve_chr.o \
	obj/ft_resolve_uns.o \
	obj/ft_resolve_ptr.o \
	obj/ft_resolve_str.o \
	obj/ft_printf_puts.o \
	obj/ft_printf_utils.o \
	obj/ft_resolve_hex.o

all: $(NAME)
	
$(NAME):  $(OBJ_FILES)
	@printf "\n$(CY)Generating %s lib ...$(CY)" $@
	@ar -rcs $@ $^
	@printf "$(CY)Done !$(CY)\n" $@

obj/%.o: %.c
	@printf "\n$(BLUE_BACK)Generating %s object ...$(RE)\n" $@
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $<

clean:
	@printf "\n$(RED_BACk)removing all objects ...$(RE)\n" $@
	@rm -f $(OBJ_FILES)

fclean: clean
	@printf "\n$(RED_BACk)removing lib ...$(RE)\n" $@
	@rm -f $(NAME)

re: fclean all

bonus: $(OBJ) $(BONUS_OBJ)
	ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)
	echo "$(NAME) created"

.PHONY: all, clean, fclean, re, run, bonus

RE	= \033[0m
BLUE_BACK	= \033[1m\033[44m
RED_BACk	= \033[1m\033[41m
CY	= \033[36;1m
RC	= \033[0m