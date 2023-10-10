#include "libftprintf.h"

int	count_length_to_print(t_list *lst)
{
	t_list	*tmp;
	int		count;

	tmp = lst;
	count = 0;
	while (tmp != NULL)
	{
		count += ft_strlen(tmp->content);
		tmp = tmp ->next;
	}
	return (count);
}

int	print_str(t_list *lst)
{
	t_list	*tmp;
	int		len_str;
	int		len_to_add;
	char	*str_to_print;
	int		tmplen;

	tmp = lst;
	len_str = count_length_to_print(lst);
	if (len_str == 0)
		return (-1);
	str_to_print = malloc(sizeof(char) * len_str + 1);
	if (str_to_print == NULL)
		return (-1);
	len_to_add = 0;
	while (tmp)
	{
		tmplen = ft_strlen(tmp->content);
		ft_strlcpy(&str_to_print[len_to_add], tmp->content, ((size_t)(tmplen + 1)));
		len_to_add += tmplen;
		tmp = tmp ->next;
	}
	ft_putstr_fd(str_to_print, 1);
	return (len_to_add);
}

char	*get_pointer_str(va_list args)
{
	char	*tmp;
	char	*ret;

	tmp = ft_utoabase((size_t)va_arg(args, void *), 16, 0);
	ret = ft_strndup("0x", (ft_strlen(tmp) + 3));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(&(ret[2]), tmp, ft_strlen(tmp) + 1);
	return (ret);
}

int	add_new_node(char *str, t_list **lst)
{
	t_list	*new_node;

	if (!str)
		return (-1);
	new_node = ft_lstnew(str);
	if (!new_node)
		return (-1);
	ft_lstadd_back(lst, new_node);
	return (0);
}

char	*args_are_string_or_char(va_list args, char *str)
{
	char	*tmp;
	char	c;

	if (str[0] != '%')
		return (str);
	if (str[1] == 's')
	{
		tmp = va_arg(args, char *);
		return (ft_strndup(tmp, ft_strlen(tmp) + 1));
	}
	if (str[1] == '%')
		c = '%';
	else if (str[1] == 'c')
		c = va_arg(args, int);
	tmp = malloc(sizeof(char) * 2);
	if (tmp == NULL)
		return (NULL);
	tmp[0] = c;
	tmp[1] = '\0';
	return (tmp);
}

char	*format_args(va_list args, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (str[0] != '%' || str[1] == '%' || str[1] == 'c' || str[1] == 's')
		tmp = args_are_string_or_char(args, str);
	else if (str[1] == 'u')
		tmp = ft_utoabase(va_arg(args, unsigned int), 10, 0);
	else if (str[1] == 'x')
		tmp = ft_utoabase(va_arg(args, size_t), 16, 0);
	else if (str[1] == 'X')
		tmp = ft_utoabase(va_arg(args, size_t), 16, 1);
	else if (str[1] == 'i')
		tmp = ft_itoabase(va_arg(args, int), 10);
	else if (str[1] == 'd')
		tmp = ft_itoabase(va_arg(args, size_t), 10);
	else if (str[1] == 'p')
		tmp = get_pointer_str(args);
	return (tmp);
}

int	fill_list(char *str, va_list args, t_list *lst)
{
	int		n;
	int		checker;

	while (*str)
	{
		n = 0;
		while (*(str + n) != '%' && *(str + n) != '\0')
			n++;
		if (n == 0 && *str != '\0')
			n = 3;
		checker = add_new_node(format_args(args, ft_strndup(str, n)), &lst);
		if (checker == -1)
			return (-1);
		if (*str == '%')
			n--;
		str += n;
	}
	return (print_str(lst));
}

int	ft_printf(const char *str, ...)
{
	va_list args;
	t_list	*lst;
	int		ret;

	if (!str)
		return (-1); // make a pretty error message + an exit shit ?
	if (!(*str))
		return (0);
	lst = NULL;
	// error check in str
	va_start(args, str);
	ret = fill_list((char *)str, args, lst);
	va_end(args);
	return (ret);
}
