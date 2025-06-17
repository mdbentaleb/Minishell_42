/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:12:43 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/05 14:43:49 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	expand_handle_special_vars(char *line, char **result, t_data *dt)
{
	char	*tmp;
	char	*tmp_res;

	if (line[dt->i + 1] == '?')
	{
		tmp = ft_itoa(dt->exitstatus);
		tmp_res = ft_strjoin(*result, tmp);
		free(tmp);
		free(*result);
		*result = tmp_res;
		dt->i += 2;
		dt->start = dt->i;
	}
	else if (line[dt->i + 1] == '0')
	{
		tmp_res = ft_strjoin(*result, "zmbash");
		free(*result);
		*result = tmp_res;
		dt->i += 2;
		dt->start = dt->i;
	}
}

static void	handle_empty_or_normal_var(char *line, char **result, t_data *dt)
{
	char	*key;
	char	*expanded;
	char	*tmp_res;

	if (dt->var_end == dt->var_start)
	{
		tmp_res = ft_strjoin(*result, "$");
		free(*result);
		*result = tmp_res;
		dt->i++;
		dt->start = dt->i;
		return ;
	}
	key = ft_substr(line, dt->var_start, dt->var_end - dt->var_start);
	expanded = ft_expand_vars(dt, key);
	free(key);
	if (!expanded)
		expanded = ft_strdup("");
	tmp_res = ft_strjoin(*result, expanded);
	free(expanded);
	free(*result);
	*result = tmp_res;
	dt->i = dt->var_end;
	dt->start = dt->i;
}

static void	expand_normal_variable(char *line, char **result, t_data *dt)
{
	dt->var_start = dt->i + 1;
	dt->var_end = dt->var_start;
	if (ft_isdigit(line[dt->var_start]))
		dt->var_end++;
	else
	{
		while (line[dt->var_end] && (ft_isalnum(line[dt->var_end])
				|| line[dt->var_end] == '_'))
			dt->var_end++;
	}
	handle_empty_or_normal_var(line, result, dt);
}

static void	expand_heredoc_loop(char *line, char **result, t_data *dt)
{
	char	*tmp;
	char	*tmp_res;

	if (line[dt->i] == '$' && line[dt->i + 1])
	{
		if (ft_if_should_skip(line[dt->i + 1]))
		{
			dt->i++;
			return ;
		}
		tmp = ft_substr(line, dt->start, dt->i - dt->start);
		tmp_res = ft_strjoin(*result, tmp);
		free(tmp);
		free(*result);
		*result = tmp_res;
		if (line[dt->i + 1] == '?' || line[dt->i + 1] == '0')
			expand_handle_special_vars(line, result, dt);
		else
			expand_normal_variable(line, result, dt);
	}
	else
		dt->i++;
}

char	*expand_heredoc_preserve_quotes(char *line, t_data *dt)
{
	char	*result;
	char	*tmp;
	char	*tmp_res;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	dt->start = 0;
	dt->i = 0;
	while (line[dt->i])
		expand_heredoc_loop(line, &result, dt);
	if (dt->start < (int)ft_strlen(line))
	{
		tmp = ft_substr(line, dt->start, ft_strlen(line) - dt->start);
		if (!tmp)
			return (free(result), NULL);
		tmp_res = ft_strjoin(result, tmp);
		free(tmp);
		free(result);
		if (!tmp_res)
			return (NULL);
		result = tmp_res;
	}
	return (result);
}
