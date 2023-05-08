#include "libftprintf.h"

// t_list *ft_lstlast(t_list *lst)

void	ft_lstfree(t_list **lst)
{	t_list	*tmp;

	while (*lst != NULL)
	{
		tmp = ((*lst)->next);
		free((*lst)->s);
		free((*lst)->next);
		free(*lst);
		*lst = tmp;
	}
	free(lst);
}
