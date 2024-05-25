#include <minishell.h>

static void	free_content(void *content)
{
	if (content != NULL)
		ft_free((void **)&content);
}

void	*free_one_lal(void *ptr)
{
	t_list	*lalloc;

	lalloc = allocs();
	if (ptr == NULL)
		return (NULL);
	while (lalloc)
	{
		if (lalloc->content == ptr)
		{
			ft_lstdelone(lalloc, free_content);
			return (NULL);
		}
		lalloc = lalloc->next;
	}
	ft_printf("free_one_lal, pointer wasn't in the list or was NULL");
	return (NULL);
}

void	clear_lal()
{
	t_list *lalloc;

	lalloc = allocs();
	ft_lstclear(&lalloc, free_content);
}

void	add_to_lal(void *ptr)
{
	t_list	*lalloc;
	t_list	*new_node;

	new_node = ft_lstnew(ptr);
	if (!new_node)
		ft_error(FATAL, ERR_ALLOC, 1);
	lalloc = allocs();
	ft_lstadd_front(&lalloc, new_node);
}