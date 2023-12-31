#include "../../headers/minishell.h"

t_list	*freekeyvalue(char *key, char *value)
{
	free(key);
	free(value);
	return (NULL);
}

int	count_words(t_list *tokens)
{
	int	words;

	words = 0;
	if (((t_token *)tokens->content)->id == Pipe)
		tokens = tokens->next;
	while (tokens)
	{
		if (((t_token *)tokens->content)->id == Pipe)
			break ;
		words++;
		tokens = tokens->next;
	}
	return (words);
}

char	**get_args_exec(t_list *tokens)
{
	int		i;
	char	**new;

	i = 0;
	new = malloc(sizeof(char *) * (count_words(tokens) + 1));
	ft_malloc_fail_check(new);
	if (((t_token *)tokens->content)->id == Pipe)
		tokens = tokens->next;
	while (tokens)
	{
		if (((t_token *)tokens->content)->id == Pipe)
			break ;
		new[i] = ft_strdup(((t_token *)tokens->content)->word);
		if (!new[i])
			ft_disruptive_exit("malloc fail", 1);
		tokens = tokens->next;
		i++;
	}
	new[i] = NULL;
	return (new);
}

int	ms_lstadd_pipe(t_list **pipes, char **tokenarr)
{
	t_list	*new;
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	if (pipe == NULL)
		ft_disruptive_exit("malloc fail", 1);
	pipe->tokens = tokenarr;
	new = ft_lstnew((void *)pipe);
	if (new == NULL)
	{
		free(pipe);
		ft_disruptive_exit("malloc fail", 1);
	}
	ft_lstadd_back(pipes, new);
	return (0);
}

t_list	*ms_parser(t_list **tokens)
{
	t_list	*pipes;
	char	**new;

	pipes = 0;
	new = get_args_exec(*tokens);
	if (!new)
		ft_disruptive_exit("malloc fail", 1);
	ms_lstadd_pipe(&pipes, new);
	while (*tokens)
	{
		if (((t_token *)(*tokens)->content)->id == Pipe)
		{
			new = get_args_exec(*tokens);
			if (!new)
				ft_disruptive_exit("malloc fail", 1);
			ms_lstadd_pipe(&pipes, new);
		}
		tokens = &((*tokens)->next);
	}
	return (pipes);
}
