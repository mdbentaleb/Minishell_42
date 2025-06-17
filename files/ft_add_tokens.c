/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:01:33 by ouzouini          #+#    #+#             */
/*   Updated: 2025/06/05 11:01:28 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->value);
		free(head);
		head = tmp;
	}
}

int	ft_add_token(t_token **tokens, t_token_type type, char *value)
{
	t_token	*node;
	t_token	*cur;

	node = malloc(sizeof(t_token));
	if (node == NULL)
		return (1);
	node->value = ft_strdup(value);
	if (!node->value)
		return (1);
	node->type = type;
	node->next = NULL;
	node->prev = NULL;
	if (!*tokens)
		*tokens = node;
	else
	{
		cur = *tokens;
		while (cur->next)
			cur = cur->next;
		cur->next = node;
		node->prev = cur;
	}
	return (0);
}
