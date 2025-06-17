/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_util_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:53:14 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/05 13:08:21 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_handle_lexer_pipe(t_token **tokenslst)
{
	if (ft_add_token(tokenslst, PIPE, "|"))
		return (1);
	return (0);
}

int	ft_hndl_lxr_in(t_token **tokenslst, t_data *dt, int *start, int *end)
{
	if (dt->input[*end + 1] == '<')
	{
		if (ft_add_token(tokenslst, HERDC, "<<"))
			return (1);
		(*start) += 1;
	}
	else
	{
		if (ft_add_token(tokenslst, RD_IN, "<"))
			return (1);
	}
	return (0);
}

int	ft_hndl_lxr_out(t_token **tokenslst, t_data *dt, int *start, int *end)
{
	if (dt->input[*end + 1] == '>')
	{
		if (ft_add_token(tokenslst, APPND, ">>"))
			return (1);
		(*start) += 1;
	}
	else
	{
		if (ft_add_token(tokenslst, RD_OUT, ">"))
			return (1);
	}
	return (0);
}

int	ft_split_input(t_token **tokenslst, t_data *dt, int *start, int *end)
{
	if (dt->input[*end] == '|')
	{
		if (ft_add_token(tokenslst, PIPE, "|"))
		{
			if (ft_handle_lexer_pipe(tokenslst))
				return (1);
		}
	}
	else if (dt->input[*end] == '<')
	{
		if (ft_hndl_lxr_in(tokenslst, dt, start, end))
			return (1);
	}
	else if (dt->input[*end] == '>')
	{
		if (ft_hndl_lxr_out(tokenslst, dt, start, end))
			return (1);
	}
	(*start)++;
	return (0);
}

void	ft_split_input2(t_data *dt, int *end)
{
	char	quote;

	while (dt->input[*end] && dt->input[*end] != ' '
		&& dt->input[*end] != '|' && dt->input[*end] != '<'
		&& dt->input[*end] != '>')
	{
		if (dt->input[*end] == '\'' || dt->input[*end] == '\"')
		{
			quote = dt->input[(*end)++];
			while (dt->input[*end] && dt->input[*end] != quote)
				(*end)++;
			if (dt->input[*end] == quote)
				(*end)++;
		}
		else
			(*end)++;
	}
}
