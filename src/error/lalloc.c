#include <minishell.h>

static void	free_content(void *content)
{
	if (content != NULL)
	{
		free(content);
		content = NULL;
	}
}

void	ft_lst_remove_if(t_list **lst, void *data_ref,
							int (*cmp)(void *, void *), void (*del)(void *))
{
	t_list	*cur;
	
	if (lst == NULL || *lst == NULL)
		return ;
	cur = *lst;
	if (cmp(cur->content, data_ref) == 0)
	{
		*lst = cur->next;
		ft_lstdelone(cur, del);
		ft_lst_remove_if(lst, data_ref, cmp, del);
	}
	else
	{
		cur = *lst;
		ft_lst_remove_if(&cur->next, data_ref, cmp, del);
	}
}

int	same_ptr(void *ptr, void *ptr2)
{
	if (ptr == ptr2)
		return (0);
	return (1);
}

void	free_one_lal(void *ptr)
{
	ft_lst_remove_if(allocs(), ptr, same_ptr, free_content);
}

void	clear_lal()
{
	t_list	**lalloc;

	lalloc = allocs();
	ft_lstclear(lalloc, free_content);
}

void	add_to_lal(void *ptr)
{
	t_list	**lalloc;
	t_list	*new_node;

	new_node = ft_lstnew(ptr);
	if (!new_node)
		ft_error(E_CODE_ERRNO + errno);
	lalloc = allocs();
	ft_lstadd_front(lalloc, new_node);
}

void	ft_free(void **ptr)
{
	if (*ptr)
	{
		free_one_lal(*ptr);
		*ptr = NULL;
	}
}
