#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stddef.h>

int		ft_printf(const char *str, ...);
int		fill_list(char *str, va_list args, t_list *lst);
char	*format_args(va_list args, char *str);
char	*get_string_char(va_list args, char *str);
int		search_format_specifier(char *str);
int		print_str(t_list *lst);
int		add_new_node(char *str, t_list **lst);
char	*get_pointer_adress(va_list args);
int		count_length_to_print(t_list *lst);
char	*char_to_str(char c);

#endif
