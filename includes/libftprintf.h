#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stddef.h>


typedef struct	s_list
{
	char	*s;
	t_list	*next;
}				t_list;

int	(*get_arg)(int, int);

int		ft_printf(const char *str, ...);
int		write_and_get_written_nb(char *str, va_list args);
int		fill_and_print(char *str, va_list args, t_list **lst);
t_list	*create_new_node(t_list *lst, char *content, int content_size);
char	*ft_strndup(const char *s, int n);
int		print_str(t_list **lst);
int 	count_printed_length(t_list **lst);

#endif
