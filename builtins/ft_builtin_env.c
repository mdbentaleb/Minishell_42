/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:38:37 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/03 14:55:52 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtin_env(t_data *dt)
{
	t_env	*cur;

	cur = dt->env;
	while (cur)
	{
		if (cur->key && cur->value)
		{
			ft_putstr_fd(cur->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(cur->value, 1);
		}
		cur = cur->next;
	}
	return (0);
}
