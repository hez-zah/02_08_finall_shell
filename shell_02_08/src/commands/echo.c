#include "../../headers/minishell.h"

static void print_string(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
}

static int  count_dash_n(char **cmd)
{
	int	count;
	int	i;

	count = 0;
	while (cmd[count] && cmd[count][0] == '-' && cmd[count][1] == 'n')
	{
		i = 1;
		while (cmd[count][i])
		{
			if (cmd[count][i] != 'n')
				return (count);
			i++;
		}
		count++;
	}
	return (count);
}

int cmd_echo(char **cmd)
{
	int ncount;

	if (ft_strncmp(cmd[0], "echo", 5) != 0)
		return (1);
	ncount = count_dash_n(&cmd[1]);
	print_string(&cmd[1 + ncount]);
	if (ncount == 0)
		write(1, "\n", 1);
    return (0);
}
