/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_comands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:15:23 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/03 16:27:01 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**my_realloc_args(char **old, int old_count, int new_count)
{
	char	**new_args;
	int		i;

	new_args = malloc(sizeof(char *) * (new_count + 1));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < old_count)
	{
		new_args[i] = old[i];
		i++;
	}
	new_args[new_count] = NULL;
	free(old);
	return (new_args);
}

int	ft_add_argument(char ***args, int *count, char *value)
{
	char	**new_arg;

	new_arg = my_realloc_args(*args, *count, *count + 1);
	if (!new_arg)
		return (1);
	new_arg[*count] = ft_strdup(value);
	if (!new_arg[*count])
		return (ft_free_double(new_arg), 1);
	*args = new_arg;
	(*count)++;
	(*args)[*count] = NULL;
	return (0);
}

static int	init_redirect(t_token **cur, t_redirect **redir)
{
	*redir = malloc(sizeof(t_redirect));
	if (!*redir)
		return (1);
	if ((*cur)->type == RD_OUT)
		(*redir)->type = RED_OUT;
	else if ((*cur)->type == APPND)
		(*redir)->type = RED_APPEND;
	else if ((*cur)->type == RD_IN)
		(*redir)->type = RED_IN;
	else if ((*cur)->type == HERDC)
		(*redir)->type = RED_HEREDOC;
	(*cur) = (*cur)->next;
	(*redir)->file = ft_strdup((*cur)->value);
	if (!(*redir)->file)
		return (free(*redir), 1);
	(*redir)->next = NULL;
	return (0);
}

int	ft_add_redirecs(t_token **cur, t_redirect **redirects)
{
	t_redirect	*redir;
	t_redirect	*tmp;

	if (init_redirect(cur, &redir))
		return (1);
	if (!*redirects)
		*redirects = redir;
	else
	{
		tmp = *redirects;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
	return (0);
}

t_cmd	*create_cmd_node(char **args, t_redirect *redirects)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = args;
	new_cmd->redirect = redirects;
	new_cmd->next = NULL;
	return (new_cmd);
}
