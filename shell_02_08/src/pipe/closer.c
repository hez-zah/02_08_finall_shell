#include "../../headers/minishell.h"

void	close_pip_file(t_pip *pip)
{
	close(pip->herd_in);
	if (pip->pip_in != 0)
		close(pip->pip_in);
	if (pip->pip_out != 1)
		close(pip->pip_out);
}

void	close_file(t_pip *pip)
{
		close(pip->herd_in);
}
void	close_fd_all(t_pip *all)
{
	t_pip	*pip;

	pip = all;
	while (pip)
	{
		if (pip->pip_in != 0)
			close(pip->pip_in);
		if (pip->pip_out != 1)
			close(pip->pip_out);
		pip = pip->next_pip;
	}
}

void	close_herd_file(t_pip *all)
{
	t_pip	*pip;

	pip = all;
	while (pip)
	{
		close(pip->herd_in);
		pip = pip->next_pip;
	}
}