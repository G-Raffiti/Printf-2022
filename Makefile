.PHONY: all clean fclean re

NAME = libftprintf.a
CC = gcc
CC_FLAGS = -Wall -Wextra -Werror
SRCS = ft_itoabase.c ft_lstfree.c ft_printf.c ft_strlcpy.c ft_strlen.c ft_strndup.c \
ft_utoabase.c
OBJS = $(SRCS:.c=.o)
INC = libftprintf.h

#*****************************************************************************#
#                                   Rules                                     #
#*****************************************************************************#

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

#*****************************************************************************#
#                                Compilation                                  #
#*****************************************************************************#

%.o: %.c
	$(CC) $(CC_FLAGS) -o $@ -c $<

$(NAME): $(OBJS) $(INC)
	ar rcs $(NAME) $(OBJS)
