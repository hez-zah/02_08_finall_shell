#include "../../headers/minishell.h"

static int  ft_cmdlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	cmd_exit(char **cmd, int last_return)
{
	int	exitcode;
	int	errorcode;
	int	cmdlen;

	errorcode = 0;
	cmdlen = ft_cmdlen((void *)cmd);
	if (cmdlen > 2)
	{
		write(2, "BRO: exit: too many arguments\n", 30);
		return (1);
	}
	if (cmdlen == 1)
		exit(last_return);
	exitcode = exit_atoi(cmd[1], &errorcode);
	if (errorcode != 0)
	{
		write(2, "BRO: exit: ", 11);
		write(2, cmd[1], ft_strlen(cmd[1]));
		write(2, ": numeric argument required\n", 28);
		exit(255);
	}
	exit(exitcode);
}
