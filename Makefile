.PHONY: all clean fclean re libft

NAME = libftprintf.a
CC = gcc
CC_FLAGS = -Wall -Wextra -Werror
SRCS = ft_printf.c ft_printf_tools.c
OBJS = $(SRCS:.c=.o)
INC = libftprintf.h
INCLIBFT = libft/libft.h

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
	$(CC) $(CC_FLAGS) -o $@ -c $< -I $(INC) -I $(INCLIBFT)
