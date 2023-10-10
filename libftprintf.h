#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stddef.h>


// typedef struct	s_list
// {
// 	char	*s;
// 	struct s_list	*next;
// }				t_list;

int		ft_printf(const char *str, ...);
int		write_and_get_written_nb(char *str, va_list args);
int		fill_list(char *str, va_list args, t_list *lst);
char	*format_args(va_list args, char *str);
char	*get_pointer_str(va_list args);
int		add_new_node(char *str, t_list **lst);
int		print_str(t_list *lst);
int		count_length_to_print(t_list *lst);

#endif
