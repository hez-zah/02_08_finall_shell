#include "../../headers/minishell.h"

void	print_err(char *led)
{
	write(2, led, ft_strlen(led));
	write(2, ": No such file or directory. ", 29);
	write(2, "\n", 1);
}

void	checkdir(char *led, char **str, char **env)
{
	struct stat path_stat;

	stat(led, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		write(2, led, ft_strlen(led));
		write(2, ": is a directory.\n", 18);
		exit(126);
	}
	else
	{
		execve(led, str, env);
		write(2, led, ft_strlen(led));
		write(2, ": command not found\n", 21);
	}
}

void	exec_child(char *led, t_pip *pip, t_pia *pia)
{
	if (ft_patht(led, pia->old_env) && led)
		execve(ft_patht(led, pia->old_env), pip->pip_arg, pia->old_env);
	else
	{
		write(2, led, ft_strlen(led));
		write(2, ": command not found\n", 21);
	}
}

void	dup_fd_close(t_pip *pip, t_pia *pia)
{
	dup2(pip->pip_in, 0);
	dup2(pip->pip_out, 1);
	close_fd_all(pia->all);
	close_herd_file(pia->all);
}

void	child_red_pip(t_pia *pia, t_pip  *pip, t_mini *data)
{
	char	*led;
	int		last_return;

	last_return = 0;
	dup_fd_close(pip, pia);
	led = pip->pip_arg[0];
	if (exp_uns(pip->pip_arg[0]))
	{
		if (exp_uns(pip->pip_arg[0]) == 1)
		{
			pia->old_env = ft_export_unset(pip, pia->old_env, set_env(pia->old_env));
			last_return = pip->spc_return;
		}
		else if ((exp_uns(pip->pip_arg[0]) == 2))
			last_return = exe_buildin(pia->old_env, pip, data);
		exit(last_return);
	}
	else if (!access(led, F_OK))
		checkdir(led, pip->pip_arg, pia->old_env);
	else if (access(led, F_OK) && !ft_strnstr(led, "/", ft_strlen(led)))
		exec_child(led, pip, pia);
	else
		print_err(led);
	exit(127);
}
