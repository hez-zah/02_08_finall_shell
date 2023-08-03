#include "../../headers/minishell.h"

int		error_unset(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]))
			return (0);
	return (1);
}

int  compar_args(char *str)
{
	int k;

	k = 0;
	while (str[k] && str[k] != '=')
		k++;
	return (k);
}

char **conver_env_unset(char **env, char *delet, int nbr)
{
	char	**led;
	int		i;
	int		j;

	led = (char **)malloc(sizeof(char *) * nbr);
	i = -1;
	j = 0;
	while (env[++i])
	{
		if (!ft_strncmp(delet, env[i], compar_args(env[i])))
			i++;
		led[j] = ft_strdup(env[i]);
		j++;
	}
	led[j] = NULL;
	freeDoublePointer(env);
	return (led);
}

char	**ft_unset(t_pip *pip, char **new_env, char **str, int nbr)
{
	int n;

	n = 0;
	pip->spc_return = 0;
	while (str[++n])
	{
        if (!ft_strncmp(str[n], "#", 1))
			break;
		if (!ft_strncmp(str[n], "=", 1) || !error_unset(str[n]))
		{
			write(2, " unset: `", 9);
			write(2, str[n], ft_strlen(str[n]));
			write(2, "': not a valid identifier\n", 27);
			pip->spc_return = 1;
		}
		else
			new_env = conver_env_unset(new_env, str[n], nbr--);
	}
	return (new_env);
}
