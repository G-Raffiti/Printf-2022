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

char	*get_pointer_str(va_list args, t_list *lst)
{
	char *tmp;
	char *ret;
	tmp = ft_utoabase((size_t)va_arg(args, void *), 16, 0);
	ret = ft_strndup("0x", (ft_strlen(tmp) + 3));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(&(ret[2]), tmp, ft_strlen(tmp));
	return (ret);
}

t_list	*formart_args(va_list args, t_list *lst)
{
	char *tmp;

	tmp = NULL;
	if (lst->s[1] == 'c' || lst->s[1] == '%' || lst->s[1] == 's')
		tmp = va_arg(args, char *);
	else if (lst->s[1] = 'u')
		tmp = ft_utoabase(va_arg(args, size_t), 10, 0);
	else if (lst->s[1] = 'x')
		tmp = ft_utoabase(va_arg(args, size_t), 16, 0);
	else if (lst->s[1] = 'X')
		tmp = ft_utoabase(va_arg(args, size_t), 16, 1);
	else if (lst->s[1] = 'i')
		tmp = ft_itoabase(va_arg(args, int), 10, 0);
	else if (lst->s[1] = 'd')
		tmp = ft_itoabase(va_arg(args, size_t), 10, 0);
	else if (lst->s[1] = 'p')
		tmp = get_pointer_str(args, lst);
	free(lst->s);
	if (tmp != NULL)
		lst->s = ft_strndup(tmp, (ft_strlen(tmp) + 1));
	else
		lst->s = NULL;
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
		*lst = format_args(args, *lst);
		if ((*lst)->s == NULL)
			return (-1);
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
