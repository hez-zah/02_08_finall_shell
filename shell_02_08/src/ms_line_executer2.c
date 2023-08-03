#include "../headers/minishell.h"

int		exp_uns(char *led)
{
	if (!ft_strncmp(led, "export", 6) ||
		!ft_strncmp(led, "unset", 5) ||
		!ft_strncmp(led, "env", 3))
			return (1);
	if (!ft_strncmp(led, "cd", 2) ||
		!ft_strncmp(led, "echo", 4) ||
		!ft_strncmp(led, "exit", 4) ||
		!ft_strncmp(led, "pwd", 3))
			return (2);
	return (0);
}

char	**ft_export_unset(t_pip *pip, char **new_env, int nbr)
{
	char	**str;

	str = pip->pip_arg;
	if (!ft_strncmp(str[0], "export", 6))
		new_env = ft_export(new_env, str, nbr, pip);
	else if (!ft_strncmp(str[0], "unset", 5))
		new_env = ft_unset(pip, new_env, str, nbr);
	else if (!ft_strncmp(str[0], "env", 3))
		pip->spc_return = reel_env(str, new_env);
	return (new_env);
}

int	exe_buildin(char **new_env, t_pip *pip, t_mini *data)
{
	if (!ft_strcmp(pip->pip_arg[0], "echo"))
		return (cmd_echo(pip->pip_arg));
	if (!ft_strcmp(pip->pip_arg[0], "cd"))
		return (cmd_cd(pip->pip_arg, new_env));
	if (!ft_strcmp(pip->pip_arg[0], "exit"))
		return (cmd_exit(pip->pip_arg, data->last_return));
	if (!ft_strcmp(pip->pip_arg[0], "pwd"))
		return (cmd_pwd(pip->pip_arg, new_env));
	return (1);
}