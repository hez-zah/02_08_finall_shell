#include "../../headers/minishell.h"

void	signal_cmd(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	free_fd(int **fd)
{
	int	i;

	i = 0;
	while (fd[i])
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

int		len_cmd(t_pip *pip)
{
	int	i;

	i = 0;
	while (pip)
	{
		i++;
		pip = pip->next_pip;
	}
	return (i);
}

void	aid_pip_init(t_pip *tmp, int **fd, int i)
{
	if (pipe(fd[i]) < 0)
		perror("error");
	if (tmp->index == 0)
		tmp->pip_in = 0;
	else
		tmp->pip_in = fd[i - 1][0];
	if (tmp->next_pip == NULL)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		tmp->pip_out = 1;
	}
	else
		tmp->pip_out = fd[i][1];
}

t_pip	*init_pip(t_pip *pip)
{
	t_pip	*tmp;
	int		**fd;
	int		i;

	i = 0;
	tmp = pip;
	fd = malloc(sizeof(int *) * (len_cmd(tmp) + 1));
	fd[len_cmd(tmp)] = NULL;
	while (tmp)
	{
		fd[i] = malloc(sizeof(int) * (2));
		aid_pip_init(tmp, fd, i);
		tmp = tmp->next_pip;
		i++;
	}
	free_fd(fd);
	return (pip);
}
