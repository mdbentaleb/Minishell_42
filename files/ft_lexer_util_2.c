/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_util_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:06:55 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/03 15:28:08 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_init_dt(int *i, int *j, char *quote)
{
	*i = 0;
	*j = 0;
	*quote = 0;
}

static void	ft_increment(char *quote, int *i)
{
	*quote = 0;
	(*i)++;
}

char	*remove_quotes(const char *str)
{
	int		i;
	int		j;
	char	*tmp;
	char	quote;

	ft_init_dt(&i, &j, &quote);
	tmp = malloc(ft_strlen(str) + 1);
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
		{
			quote = str[i];
			i++;
		}
		else if (quote && str[i] == quote)
			ft_increment(&quote, &i);
		else
			tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}
