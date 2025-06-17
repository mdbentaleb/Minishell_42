/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_unset_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:34:49 by ouzouini          #+#    #+#             */
/*   Updated: 2025/06/03 14:56:42 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valide_arg(char *str, int check)
{
	int	i;

	i = 1;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_')) 
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			return (check);
		if (!ft_isalnum(str[i]) && str[i] != '_') 
			return (0);
		i++;
	}
	return (1);
}
