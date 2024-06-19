FT_PRINTF_PATH = ft_printf
FT_PRINTF_SRCS = $(addprefix $(FT_PRINTF_PATH)/, ft_printf.c ft_printchar.c ft_printstr.c ft_printptr.c ft_printnum.c ft_printunum.c ft_printbnum.c)


SRCS = get_next_line1.c ft_realloc.c ft_isspace.c get_next_line.c ft_striteri.c ft_substr.c ft_strtrim.c ft_strmapi.c ft_strjoin.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_putchar_fd.c ft_itoa.c ft_tolower.c ft_toupper.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_isalpha.c ft_isdigit.c ft_isascii.c ft_isprint.c ft_isalnum.c ft_calloc.c ft_atoi.c ft_bzero.c ft_memcmp.c ft_memset.c ft_putstr.c ft_strcpy.c ft_strlen.c ft_memccpy.c ft_memcpy.c ft_putchar.c ft_split.c ft_strdup.c ft_strncat.c ft_memchr.c ft_memmove.c ft_putnbr.c ft_strcat.c ft_strlcat.c ft_strncpy.c
SRCS += $(FT_PRINTF_SRCS)

BONUS_SRCS = ft_lstsize.c ft_lstnew.c ft_lstmap.c ft_lstlast.c ft_lstiter.c ft_lstdelone.c ft_lstclear.c ft_lstadd_front.c ft_lstadd_back.c 

OBJS = $(SRCS:.c=.o)
BONUS_OBJS =$(BONUS_SRCS:.c=.o)

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

bonus: $(OBJS) $(BONUS_OBJS)
	@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
