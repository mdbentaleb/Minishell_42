/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:51:08 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/04 10:58:12 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*copy;

	copy = malloc(n + 1);
	if (!copy)
		return (NULL);
	ft_strncpy(copy, s, n);
	copy[n] = '\0';
	return (copy);
}
