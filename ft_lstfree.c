#include "libft.h"
#include <stdio.h>
void	ft_lstfree(t_list **lst)
{
	t_list	*tmp;
    t_list  *current;

    current = *lst;
	while (current != NULL)
	{
		tmp = (current->next);
		free(current->content);
		free(current);
		current = tmp;
	}
    *lst = NULL;
}
