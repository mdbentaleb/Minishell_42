/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:52:28 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/03 15:02:59 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_env(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->key)
			free(head->key);
		if (head->value)
			free(head->value);
		free(head);
		head = tmp;
	}
}

void	ft_add_env(t_env **env, char *key, char *value)
{
	t_env	*node;
	t_env	*cur;

	node = malloc(sizeof(t_env));
	if (node == NULL)
		return ;
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = NULL;
	if (!*env)
		*env = node;
	else
	{
		cur = *env;
		while (cur->next)
			cur = cur->next;
		cur->next = node;
	}
}
