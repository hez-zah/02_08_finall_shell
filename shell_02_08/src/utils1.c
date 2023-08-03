#include "../headers/minishell.h"

t_pip	*lst_new1(void)
{
	t_pip	*one;

	one = (t_pip *)malloc(sizeof(t_pip));
	if (one == NULL)
		return (NULL);
	one->pip_in = 0;
	one->pip_out = 1;
	one->next_pip = NULL;
	return (one);
}

t_pip	*exe_lstlast(t_pip *ptr)
{
	if (!ptr)
		return (0);
	while (ptr->next_pip != NULL)
		ptr = ptr->next_pip;
	return (ptr);
}

t_pip	*lstadd_back1(t_pip *lst, t_pip *new)
{
	t_pip	*last;

	last = exe_lstlast(lst);
	if (last)
		last->next_pip = new;
	else
		lst = new;
	return (lst);
}