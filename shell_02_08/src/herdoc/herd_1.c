#include "../../headers/minishell.h"

void	creat_pipe(t_pip *pip)
{
	int fd[2];

	if (pipe(fd) < 0)
		write(2, "Error\n", 6);
	pip->herd_in = fd[0];
	pip->herd_out = fd[1];
}

void init_limit(t_pip *pip)
{
	int		i;
	int		j;

	j = 0;
	pip->limit = NULL;
	while (pip)
	{
		i = 0;
		while (pip->pip_arg[i])
		{
			if (!ft_strncmp(pip->pip_arg[i], "<<", 2) && pip->pip_arg[i + 1])
			{
				pip->limit = creat_linkdlist(pip->limit, pip->pip_arg[i + 1], j);
				j++;
			}
			i++;
		}
		pip = pip->next_pip;
	}
}

void	free_stack_herdoc(t_limit **limit)
{
	t_limit	*tmp;

	if (!limit || !(*limit))
		return ;
	while (*limit)
	{
		tmp = (*limit)->next_limit;
		free((*limit)->limit);
		free(*limit);
		*limit = tmp;
	}
	*limit = NULL;
}

int	freeDoublePointer(char **str)
{
	int	i;

	i = 0;
	if (!str || !(*str))
		return (0);
	while (str[i])
		free(str[i++]);
	free(str);
	return (1);
}
