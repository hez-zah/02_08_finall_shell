#include "../../headers/minishell.h"

int cmd_pwd(char **cmd, char **env)
{
	char    cur_pwd[PATH_MAX];

    (void)env;
	if (ft_strncmp(cmd[0], "pwd", 4) != 0)
		return (1);
    getcwd(cur_pwd, sizeof(cur_pwd));
	printf("%s\n", cur_pwd);
    return (0);
}
