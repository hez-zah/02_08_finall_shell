#include "../../headers/minishell.h"

static void show_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
	}
}

int	reel_env(char **str, char **env)
{
	if (!str[1] || str[1][0] == '#')
		show_env(env);
	else if (!access(str[1], F_OK))
	{
		write(2, "env: ", 5);
		write(2, str[1], ft_strlen(str[1]));
		write(2, ": Permission denied\n", 20);
		return (126);
	}
	else
	{
		write(2, "env: ", 5);
		write(2, str[1], ft_strlen(str[1]));
		write(2, ": No such file or directory\n", 29);
		return (127);
	}
	return (0);
}
