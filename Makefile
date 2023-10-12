.PHONY: all clean fclean re libft

NAME = libftprintf.a
CC = gcc
CC_FLAGS = -Wall -Wextra -Werror -g
SRCS = ft_printf.c ft_printf_tools.c
OBJS = $(SRCS:.c=.o)
INC = ft_printf.h
INCLIBFT = libft

#*****************************************************************************#
#                                   Rules                                     #
#*****************************************************************************#

all: $(NAME)

clean:
	rm -rf $(OBJS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

libft:
	make -C libft
	cp libft/libft.a .
	mv libft.a $(NAME)

#*****************************************************************************#
#                                Compilation                                  #
#*****************************************************************************#

$(NAME): libft $(OBJS) $(INC)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CC_FLAGS) -o $@ -c $< -I ./ -I $(INCLIBFT)
