#include "ft_printf.h"

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

char	*get_pointer_adress(va_list args)
{
	char	*tmp;
	char	*ret;

	tmp = ft_utoabase((size_t)va_arg(args, void *), 16, 0);
	ret = malloc(sizeof(char) * ft_strlen(tmp) + 3);
	ft_strlcpy(ret, "0x", 3);
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(&(ret[2]), tmp, ft_strlen(tmp) + 1);
	return (ret);
}

int	add_new_node(char *str, t_list **lst)
{
	t_list	*new_node;

	if (str == NULL)
		return (-1);
	new_node = ft_lstnew(str);
	free(str);
	if (!new_node)
		return (-1);
	ft_lstadd_back(lst, new_node);
	return (0);
}

char	*char_to_str(char c)
{
	char *ret;

	ret = malloc(sizeof(char) * 2);
	if (ret == NULL)
		return (NULL);
	ret[0] = c;
	ret[1] = '\0';
	return (ret);
}
