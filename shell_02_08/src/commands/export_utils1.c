#include "../../headers/minishell.h"

int	set_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	*ft_init_tab(int *b, int c, int len)
{
	int	i;

	i = 0;
	while (len > i)
	{
		b[i] = c;
		i++;
	}
	return (b);
}

int	ecrire_env(int *tab, char **env, int nbr)
{
	int i;
	int j;

	j = 0;
	while (j < nbr)
	{
		i = -1;
		while (++i < nbr)
		{
			if (tab[i] == j)
			{
				write(1, "declare -x ", 11);
				write(1, env[i], ft_strlen(env[i]));
				write (1, "\n", 1);
			}
		}
		j++;
	}
	return (0);
}

int	rand_J(int *tab)
{
	int	j;

	j = 0;
	while (tab[j] >= 0)
		j++;
	return (j);
}

int	affich_env(char **env, int nbr)
{
	int i;
	int j;
	int k;
	int tab[nbr];

	ft_init_tab((int *)tab, -1,(size_t)nbr);
	i = -1;
	while (++i < nbr)
	{
		j = rand_J(tab);
		k = j;
		tab[k] = i;
		while (j < nbr)
		{
			if (ft_strncmp(env[k], env[j],ft_strlen(env[k])) > 0 &&
				tab[j] < 0)
			{
				tab[j] = i;
				tab[k] = -1;
				k = j;
			}
			j++;
		}
	}
	return (ecrire_env(tab, env, nbr));
}
