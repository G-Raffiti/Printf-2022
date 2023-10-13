#include "libft.h"

t_list	*ft_lstnew(char *content)
{
	t_list *lst;

	lst = malloc(sizeof(t_list));
	if (lst == NULL)
		return (NULL);
	lst->content = content;
    if (lst->content == NULL)
	{
		free(lst);
		return (NULL);
	}
	lst->next = NULL;
	return (lst);
}
