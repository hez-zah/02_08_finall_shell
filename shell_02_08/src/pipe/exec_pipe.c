#include "../../headers/minishell.h"

t_pip	*redirect1(t_pip *pip)
{
	int	i;

	i = 0;
    while (pip->pip_arg[i] != NULL)
	{
		if (pip->pip_arg[i][0] == '<' || pip->pip_arg[i][0] == '>')
			file_red_pip(pip, i);
		else
			i++;
	}
	return (pip);
}

void	wait_childs(int i, pid_t *pid, t_pia *pia, t_mini *data)
{
	int	j;
	int	status;

	j = 0;
	while (j < i) 
	{
		waitpid(pid[j], &status, 0);
		if (WIFEXITED(status))
			data->last_return = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->last_return = 130;
		j++;
	}
	free(pid);
	free(pia);
}

void	child_pip(t_pip *pip, t_pia *pia, pid_t *pid, t_mini *data)
{
	pip = redirect1(pip);
	*pid = fork();
	if (!(*pid))
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_red_pip(pia, pip, data);
	}
	close_pip_file(pip);
}

t_pip	*child_process_pip(t_pip *pip, char **env, t_mini *data)
{
	int			i;
	pid_t		*pid;
	t_pip		*dmp;
	t_pia		*pia;

	i = 0;
	dmp = pip;
	pia = malloc(sizeof(t_pia));
	pia->old_env = env;
	pia->all = pip;
	pid = malloc(sizeof(pid_t) * len_cmd(pip));
	while (dmp)
	{
		child_pip(dmp, pia, &pid[i], data);
		dmp = dmp->next_pip;
		i++;
	}
	wait_childs(i, pid, pia, data);
	return (pip);
}

void	app_redir(t_pip *pip, char **env, t_mini *data)
{
	signal(SIGINT, signal_cmd);
	signal(SIGQUIT, SIG_IGN);
	init_pip(pip);
	pip = child_process_pip(pip, env, data);
}
