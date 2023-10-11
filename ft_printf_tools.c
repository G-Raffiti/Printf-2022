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
