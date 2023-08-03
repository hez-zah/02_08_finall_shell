#include "../../headers/minishell.h"

int	test_repet(char *str, char **env)
{
	int i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(str, env[i], ft_strlen(str)))
			return (1);
	return (0);
	
}

int	same_key(char **arg, char **env, int n)
{
	int i;
	char *led;

	i = 0;
	while (arg[n][i] && arg[n][i] != '=')
		i++;
	led =  ft_substr(arg[n], 0, i);
	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], led, ft_strlen(led)))
			return (1);
	return (0);
}

int		str_without_equal(char **str, int n)
{
	int i;

	i = 0;
	if (ft_isalpha(str[n][0]))
	{
		while (str[n][++i])
		{
			if (!ft_isalpha(str[n][i]) && !ft_isdigit(str[n][i]))
				return (0);
		}
	}
	else
		return (0);
	return (1);
}

int		aid_export(char **str, char **new_env, int nbr, int n)
{
	(void)nbr;
	if (!ft_isalpha(str[n][0]))
		return (0);
	if (same_key(str, new_env, n))
		return (2);
	if (test_repet(str[n], new_env))
		return (0);
	if (str_without_equal(str, n))
		return (1);
	return (1);
}
