#include "ft_printf.h"

char	*get_string_char(va_list args, char *str)
{
	char	*tmp;
	char	c;
	int		i;

	if (str[0] != '%')
		return (ft_strndup(str, ft_strlen(str) + 1));
	i = 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == 's')
	{
		tmp = va_arg(args, char *);
		if (tmp == NULL)
			return (ft_strndup("(null)", 6));
		return (ft_strndup(tmp, ft_strlen(tmp) + 1));
	}
	if (str[i] == '%')
		c = '%';
	else if (str[i] == 'c')
		c = va_arg(args, int);
	else
		return (ft_strndup(&(str[1]), 2));
	return (char_to_str(c));
}

char	*format_args(va_list args, char *str)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 1;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == 'u')
		tmp = ft_utoabase(va_arg(args, unsigned int), 10, 0);
	else if (str[i] == 'x')
		tmp = ft_utoabase(va_arg(args, size_t), 16, 0);
	else if (str[i] == 'X')
		tmp = ft_utoabase(va_arg(args, size_t), 16, 1);
	else if (str[i] == 'i')
		tmp = ft_itoabase(va_arg(args, int), 10);
	else if (str[i] == 'd')
		tmp = ft_itoabase(va_arg(args, size_t), 10);
	else if (str[i] == 'p')
		tmp = get_pointer_adress(args);
	if (tmp == NULL)
		tmp = get_string_char(args, str);
	free(str);
	return (tmp);
}

int	search_format_specifier(char *str)
{
	char	*format;
	int		i;
	int		n;

	n = 1;
	format = "cspdiuxX%";
	while (*(str + n) && *(str + n) == ' ')
		n++;
	i = 0;
	while (format[i] && *(str + n) != format[i])
		i++;
	if (format[i] == '\0')
	{
		ft_putstr_fd("Error : invalid conversion specifier \'", 2);
		write(2, &str[n], 1);
		ft_putstr_fd("\'. Supported ones are \"cspdiuxX%\".", 2);
		ft_putstr_fd(" Behavior will be undefined.\n", 2);
		return (-1);
	}
	return (n + 1);
}

int	fill_list(char *str, va_list args, t_list *lst)
{
	int	n;
	int	checker;

	while (*str)
	{
		if(*str == '%' && str[1] == '\0')
			return (0);
		n = 0;
		while (*(str + n) != '%' && *(str + n) != '\0')
			n++;
		if (n == 0 && *str == '%')
			n = search_format_specifier(str);
		if (n == -1)
		{
			str++;
			n = 1;
		}
		checker = add_new_node(format_args(args, ft_strndup(str, (size_t)n)), &lst);
		if (checker == -1)
			return (-1);
		str += n;
	}
	return (print_str(lst));
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	t_list	**lst;
	int		ret;

	if (!str)
		return (-1);
	if (!(*str))
		return (0);
	lst = malloc(sizeof(t_list **));
	if (lst == NULL)
		return (-1);
	va_start(args, str);
	ret = fill_list((char *)str, args, *lst);
	va_end(args);
	ft_lstfree(lst);
	return (ret);
}
