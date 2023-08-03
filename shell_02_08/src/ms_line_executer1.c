#include "../headers/minishell.h"

void	del_pipe(void *content)
{
	t_pipe	*pipe;

	pipe = (t_pipe *)content;
	if (pipe->tokens != NULL)
		freeDoublePointer(pipe->tokens);
	free(pipe);
}

char	**pip_arg_alloc(char **str1, char **str2)
{
	int		index;
	char	**tmp;

	(void)str1;
	index = 0;
	while (str2[index])
		index++;
	tmp = malloc(sizeof(char *) * (index + 1));
	if (!tmp)
		return (NULL);
	index = 0;
	while (str2[index])
	{
		tmp[index] = ft_strdup(str2[index]);
		index++;
	}
	tmp[index] = NULL;
	return (tmp);
}

t_pip	*pipes_to_lstpip(t_list *pipes)
{
	t_pip	*pip;
	t_pip	*new;
	int		index;

	pip = NULL;
	index = 0;
	while (pipes)
	{
		new = lst_new1();
		new->pip_arg = pip_arg_alloc(new->pip_arg, ((t_pipe *)pipes->content)->tokens);
		new->index = index;
		new->access = 0;
		pip = lstadd_back1(pip, new);
		pipes = pipes->next;
		index++;
	}
	return (pip);
}

char	**lstenv_to_arrenv(t_mini *data)
{
	int		index;
	char	**new_env;
	char	*new;
	char	*old;
	t_list	*env;
	
	env = data->env;
	index = ft_lstsize(env);
	new_env = malloc(sizeof(char *) * (index + 1));
	index = 0;
	while (env->next)
	{
		old = ft_strjoin(((t_keyval *)(env->content))->key, "=");
		new = ft_strjoin(old, ((t_keyval *)(env->content))->value);
		new_env[index++] = new;
		free(old);
		env = env->next;
	}
	old = ft_strjoin(((t_keyval *)(env->content))->key, "=");
	new = ft_strjoin(old, ((t_keyval *)(env->content))->value);
	new_env[index++] = new;
	free(old);
	new_env[index] = NULL;
	return (new_env);
}

void	ftClearPip(t_pip *pips)
{
	t_pip	*tmp;

	if (!pips)
		return ;
	while (pips)
	{
		tmp = pips->next_pip;
		freeDoublePointer(pips->pip_arg);
		free(pips);
		pips = tmp;
	}
	pips = NULL;
}