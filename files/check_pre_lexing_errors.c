/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pre_lexing_errors.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:08:36 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/05 14:25:38 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_qutes(t_data *dt)
{
	int	squote;
	int	dquote;
	int	i;

	squote = 0;
	dquote = 0;
	i = 0;
	while (dt->input[i])
	{
		if (dt->input[i] == '\\')
			i++;
		else if (dt->input[i] == '\'' && !dquote)
			squote = !squote;
		else if (dt->input[i] == '\"' && !squote)
			dquote = !dquote;
		i++;
	}
	if (squote || dquote)
	{
		ft_putendl_fd("syntax error: unclosed quote", 2);
		return (1);
	}
	return (0);
}

int	is_valid_operator(const char *str, int i)
{
	char	current;

	current = str[i];
	i++;
	if (str[i] == current)
		i++;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '<' || str[i] == '>' || str[i] == '\0' || str[i] == '|')
		return (0);
	return (1);
}

int	has_invalid_redirection(const char *str)
{
	int	s_qoute;
	int	d_quote;
	int	i;

	s_qoute = 0;
	d_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			s_qoute = !s_qoute;
		else if (str[i] == '\"')
			d_quote = !d_quote;
		else if (!s_qoute && !d_quote && (str[i] == '<' || str[i] == '>'))
		{
			if (!is_valid_operator(str, i))
				return (1);
			if (str[i] == str[i + 1])
				i++;
		}
		i++;
	}
	return (0);
}

int	ft_print_ret(char *str)
{
	ft_putendl_fd(str, 2);
	return (1);
}

int	check_pre_lexing_errors(t_data *dt)
{
	char	*tmp;

	dt->i = 0;
	tmp = ft_strtrim(dt->input, " \t\v\f\n\r");
	if (!tmp)
		return (1);
	while (tmp[dt->i])
	{
		if (tmp[dt->i] == '"' || tmp[dt->i] == '\'')
		{
			if (check_qutes(dt) == 1)
				return (free(tmp), 1);
		}
		else if (tmp[dt->i] == '>' || tmp[dt->i] == '<')
		{
			if (has_invalid_redirection(tmp))
				return (free(tmp), ft_print_ret("Invalid redirection"));
		}
		else if (tmp[0] == '|' || tmp[ft_strlen(tmp) - 1] == '|')
			return (free(tmp), ft_print_ret("syntax error: near '|'"));
		else if (tmp[dt->i] == '|' && tmp[dt->i + 1] == '|')
			return (free(tmp), ft_print_ret("syntax error: near '||'"));
		dt->i++;
	}
	return (free(tmp), 0);
}
