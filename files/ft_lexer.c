/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:48:43 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/05 13:10:54 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free_and_exit(t_data *dt, t_token **tokenslst)
{
	ft_free_tokens(*tokenslst);
	ft_free_env(dt->env);
	free(dt->input);
	exit(1);
}

static void	ft_handle_word(t_token **tokenslst, t_data *dt,
								int *start, int *end)
{
	char	*tmp;

	ft_split_input2(dt, end);
	tmp = ft_substr(dt->input, *start, *end - *start);
	if (!tmp)
		ft_free_and_exit(dt, tokenslst);
	if (ft_check_varible_add_token(tokenslst, tmp, dt))
	{
		free(tmp);
		ft_free_and_exit(dt, tokenslst);
	}
	free(tmp);
	*start = *end;
}

t_cmd	*ft_lexer(t_token **tokenslst, t_data *dt)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (dt->input[start] != '\0')
	{
		while (dt->input[start] == ' ')
			start++;
		if (dt->input[start] == '\0')
			break ;
		end = start;
		if (dt->input[end] == '|' || dt->input[end] == '<'
			|| dt->input[end] == '>')
		{
			if (ft_split_input(tokenslst, dt, &start, &end))
				ft_free_and_exit(dt, tokenslst);
		}
		else
			ft_handle_word(tokenslst, dt, &start, &end);
	}
	free(dt->input);
	return (ft_get_commands(&dt));
}
