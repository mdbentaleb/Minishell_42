/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_trim_n_cmp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:22:34 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/10 13:28:24 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_str_trim_n_cmp(char *s1, char *s2, size_t n)
{
	size_t	i;
	char	*tmp;
	int		tp;

	i = 0;
	tmp = ft_strtrim(s1, " \t\v\f\n\r");
	if (!tmp)
	{
		ft_putendl_fd("Error: memory allocation", 2);
		return (free(s1), 0);
	}
	while ((tmp[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (tmp[i] != s2[i])
		{
			tp = (unsigned char)tmp[i] - (unsigned char)s2[i];
			return (free(tmp), tp);
		}
		i++;
	}
	if (tmp[i] == ' ' || tmp[i] == '\0')
		return (free(tmp), 0);
	return (free(tmp), 1);
}
