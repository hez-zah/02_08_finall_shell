#include "../../headers/minishell.h"

int	ft_check_cmd_arg(char *str)
{
	if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, "<", 1)
		|| !ft_strncmp(str, ">", 1) || !ft_strncmp(str, "", 1))
		return (0);
	return (1);
}

int		check_infile_herd(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_strncmp(str[i], "<<", 2) && str[i + 1])
			return (1);
	return (0);
}

void		refine_args(t_pip *pip, int i)
{
	free(pip->pip_arg[i]);
	free(pip->pip_arg[i + 1]);
	pip->pip_arg[i] = NULL;
	pip->pip_arg[i + 1] = NULL;
	while (pip->pip_arg[i + 2] != NULL)
	{
		pip->pip_arg[i] = pip->pip_arg[i + 2];
		i++;
	}
	pip->pip_arg[i] = NULL;
}

void	file_red_pip(t_pip *pip, int i)
{
	if (!ft_strncmp(pip->pip_arg[i], "<<", 2))
	{
		pip->pip_in = pip->herd_in;
		refine_args(pip, i);
		return ;
	}
	else if (!ft_strncmp(pip->pip_arg[i], "<", 1) && pip->pip_arg[i + 1])
		pip->pip_in = creat_file1(pip->pip_arg[i + 1], 0);
	else if (!ft_strncmp(pip->pip_arg[i], ">>", 2) && pip->pip_arg[i + 1])
		pip->pip_out = creat_file1(pip->pip_arg[i + 1], 2);
	else if (!ft_strncmp(pip->pip_arg[i], ">", 1) && pip->pip_arg[i + 1])
		pip->pip_out =  creat_file1(pip->pip_arg[i + 1], 1);
	refine_args(pip, i);
}