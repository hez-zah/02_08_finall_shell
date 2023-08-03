
#include "../headers/minishell.h"

/////////////////

char	**execution(t_pip *pip, char **new_env, t_mini *data)
{
	int	save_in;
	int	save_out;

	if (!pip->next_pip && exp_uns(pip->pip_arg[0]))
	{
		save_in = dup(0);
		save_out = dup (1);
		pip = redirect1(pip);
		dup2(pip->pip_in, 0);
		dup2(pip->pip_out, 1);
		if (exp_uns(pip->pip_arg[0]) == 1)
		{
			new_env = ft_export_unset(pip, new_env, set_env(new_env));
			data->last_return = pip->spc_return;
		}
		else
			data->last_return = exe_buildin(new_env, pip, data);
		close(pip->pip_in);
		close(pip->pip_out);
		dup2(save_in, 0);
		dup2(save_out, 1);
	}
	else
		app_redir(pip, new_env, data);
	return (new_env);
}

int		line_executer_helper(t_mini **data, t_list **tokens)
{
	if (ft_strnstr((*data)->input, "$?", ft_strlen((*data)->input)))
		replaceexitstatus(*data);
	(*data)->input = tk_expander((*data)->input, (*data)->env);
	*tokens = ms_tokenizer((*data)->input);
	free((*data)->input);
	if (*tokens == NULL)
		return (1);
	ft_lstiter(*tokens, tk_remove_quotes);
	if (ms_lexer(*tokens) != 0)
	{
		ft_lstclear(tokens, ms_del_token);
		(*data)->last_return = 258;
		return (1);
	}
	return (0);
}

void	ms_line_executer(t_mini *data)
{
	t_list	*tokens;
	t_list	*pipes;
	t_pip	*pip;
	char	**new_env;

	tokens = NULL;
	if (line_executer_helper(&data, &tokens))
		return ;
	pipes = ms_parser(&tokens);
	ft_lstclear(&tokens, ms_del_token);
	new_env = lstenv_to_arrenv(data);
	ft_lstclear(&data->env, ev_del_keyval);
	pip = pipes_to_lstpip(pipes);
	ft_lstclear(&pipes, del_pipe);
	herdoc(pip);
	if (herdoc_signal)
		data->last_return = 130;
	else
		new_env = execution(pip, new_env, data);
	data->env = ev_init_env(new_env);
	freeDoublePointer(new_env);
	ftClearPip(pip);
}
