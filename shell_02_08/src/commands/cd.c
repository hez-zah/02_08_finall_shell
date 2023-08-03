#include "../../headers/minishell.h"

static char *ft_getenv(char *key, char **env)
{
    while (*env)
    {
        if (!ft_strncmp(key, *env, ft_strlen(key)))
            return (ft_strchr(*env, '=') + 1);
        env++;
    }
	return (NULL);
}

int cmd_cd(char **cmd, char **env)
{
	if (ft_strncmp(cmd[0], "cd", 3) != 0)
		return (1);
	if (cmd[1] == NULL)
	{
		if (chdir(ft_getenv("HOME", env)))
		{
			perror(cmd[1]);
			return (1);
		}
		return (0);
	}
	if (chdir(cmd[1]))
	{
		perror(cmd[1]);
		return (1);
	}
	return (0);
}