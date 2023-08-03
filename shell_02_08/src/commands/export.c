#include "../../headers/minishell.h"

int	print_error(char **str, int n)
{
	write(2, " export: `", 10);
	write(2, str[n], ft_strlen(str[n]));
	write(2, "': not a valid identifier\n", 27);	
	return (0);
}

char	**export_env(char **env, char *ajout, int nbr)
{
    char    **exp;
    int     i;

    exp = (char **)malloc(sizeof(char *) * (nbr + 1));
    i = 0;
    while (env[i])
    {
        if (!env[i + 1])
        {
            exp[i] = ft_strdup(ajout);
            exp[i + 1] = ft_strdup(env[i]);
            break;
        }
        exp[i] = ft_strdup(env[i]);
        i++;
    }
    exp[i + 2] = NULL;
	freeDoublePointer(env);
	return (exp);
}

char	**conver_env_export(char **str, char **env, int n)
{
	int		i;
	char	*led;
	char	*old_env;

	i = 0;
	while (str[n][i] && str[n][i] != '=')
		i++;
	led = ft_substr(str[n], 0, (size_t)i);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], led, ft_strlen(led)))
		{
			old_env = env[i];
			env[i] = ft_strdup(str[n]);
			free(old_env);
		}
	}
	free(led);
	return (env);
}

char	**ft_export(char **new_env, char **str, int nbr, t_pip *pip)
{
	int	n;

	n = 0;
	pip->spc_return = 0;
	if (!str[1])
		affich_env(new_env, nbr);
	while (str[++n])
	{
		if (!ft_strncmp(str[n], "#", 1))
		{
			affich_env(new_env, nbr);
			break;
		}
		if (aid_export(str, new_env, nbr, n) == 2)
			new_env = conver_env_export(str, new_env, n);
		else if (aid_export(str, new_env, nbr, n))
			new_env = export_env(new_env, str[n], ++nbr);
		else
		{
			print_error(str, n);
			pip->spc_return = 1;
		}
	}
	return (new_env);
}
