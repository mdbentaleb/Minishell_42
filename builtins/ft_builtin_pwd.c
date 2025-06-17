/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 12:58:23 by ouzouini          #+#    #+#             */
/*   Updated: 2025/06/05 13:12:25 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtin_pwd(t_cmd *cmd)
{
	char	*buffer;

	if (cmd->args[1] != NULL)
	{
		ft_putendl_fd("pwd: too many arguments", 2);
		return (1);
	}
	buffer = getcwd(NULL, 0);
	if (buffer == NULL)
	{
		perror("getcwd");
		return (1);
	}
	printf("%s\n", buffer);
	free(buffer);
	return (0);
}
