#include "libftprintf.h"

int	print_str(t_list *lst)
{
	t_list	*tmp;
	int		len_str;
	int		len_to_add;
	char	*str_to_print;

	tmp = lst;
	len_str = count_length_to_print(lst);
	str_to_print = malloc(sizeof(char) * len_str + 1);
	if (str_to_print == NULL)
		return (-1);
	len_to_add = 0;
	while (tmp)
	{
		ft_strlcpy(&str_to_print[len_to_add], tmp->content, (ft_strlen(tmp->content) + 1));
		len_to_add += ft_strlen(tmp->content);
		tmp = tmp ->next;
	}
	ft_putstr_fd(str_to_print, 1);
	free(str_to_print);
	return (len_to_add);
}

char	*args_are_string_or_char(va_list args, char *str)
{
	char	*tmp;
	char	c;

	if (str[0] != '%')
		return (ft_strndup(str, ft_strlen(str) + 1));
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
		tmp = get_pointer_adress(args);
	free(str);
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
	t_list	**lst;
	int		ret;

	if (!str)
		return (-1); // make a pretty error message + an exit shit ?
	if (!(*str))
		return (0);
	lst = malloc(sizeof(t_list **));
	if (lst == NULL)
		return (-1);
	// error check in str
	va_start(args, str);
	ret = fill_list((char *)str, args, *lst);
	va_end(args);
	ft_lstfree(lst);
	return (ret);
}
