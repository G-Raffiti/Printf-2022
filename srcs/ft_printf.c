#include "../includes/libftprintf.h"

int count_printed_length(t_list **lst)
{
	t_list	*tmp;
	int		count;

	tmp = *lst;
	count = 0;
	while (tmp->next != NULL)
	{
		count += ft_strlen(tmp->s);
		tmp = tmp->next;
	}
	count += ft_strlen(tmp->s);
	return (count);
}

int	print_str(t_list **lst)
{
	int	n;

	n = count_printed_length(lst);
	return (n);
}

t_list	*create_new_node(t_list *lst, char *content, int content_size)
{
	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->s = ft_strndup(content, content_size);
	lst->next = NULL;
	return (lst);
}

int	fill_and_print(char *str, va_list args, t_list **lst)
{
	int	n;
	int	i;
	char	*save;

	save = str;
	n = 0;
	while (*str)
	{
		i = n;
		while (*str != '%' && *str++)
			n++;
		*lst = create_new_node(*lst, str + i, n);
		if (!(*lst) || !(*lst)->s)
			return (-1);
		if (*str == '\0')
			return (print_str(lst));
		*lst = format_args(args, (*lst)->next); // a coder, fonction qui gère les formats
							// et mets l'argument en string dans un nouveau maillon de la liste
		str += 2;
		n += 2;
	}
	return (print_str(lst)); // a coder, fonction qui met la liste en string et qui l'affiche
}

int	write_and_get_written_nb(char *str, va_list args)
{
	t_list	**lst;
	int		written;

	lst = malloc(sizeof(t_list *) + 1);
	if (!lst)
		return (-1);
	written = fill_and_print(str, args, *lst);
	// check error return
	free(lst); // faire fonction qui free toute la liste
	return (written);
}

int	ft_printf(const char *str, ...)
{
	va_list args;
	int		written;

	if (!str)
		return (-1); // make a pretty error message + an exit shit ?
	if (!(*str))
		return (0);
	// error check in str
	va_start(args, str);
	written = write_and_get_written_nb(str, args);
	// error check
	va_end(args);
	return (written);
}
