/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_comands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:06:27 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/03 17:51:34 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free_exit(t_cmd *cmd, t_token *tokens, t_env *env, char **args)
{
	if (args)
		ft_free_double(args);
	ft_free_cmd(cmd);
	ft_free_tokens(tokens);
	ft_free_env(env);
	exit(1);
}

static void	ft_init_get_cmds_vars(t_get_cmds_vars *var, t_data **dt)
{
	var->redirects = NULL;
	var->args_count = 0;
	var->args = NULL;
	var->current = NULL;
	var->cmd_head = NULL;
	var->cur = (*dt)->lsttoken;
}

static void	ft_handle_new_command(t_get_cmds_vars *var, t_data **dt)
{
	var->new_cmd = create_cmd_node(var->args, var->redirects);
	if (!var->new_cmd)
		ft_free_exit(var->cmd_head, (*dt)->lsttoken, (*dt)->env, var->args);
	if (!var->cmd_head)
		var->cmd_head = var->new_cmd;
	else
		var->current->next = var->new_cmd;
	var->current = var->new_cmd;
	var->args = NULL;
	var->args_count = 0;
	var->redirects = NULL;
}

t_cmd	*ft_get_commands(t_data **dt)
{
	t_get_cmds_vars	var;

	ft_init_get_cmds_vars(&var, dt);
	while (var.cur)
	{
		if (var.cur->type == WORD)
		{
			if (ft_add_argument(&var.args, &var.args_count, var.cur->value))
				ft_free_exit(var.cmd_head, (*dt)->lsttoken, (*dt)->env, NULL);
		}
		else if (var.cur->type == RD_OUT || var.cur->type == APPND
			|| var.cur->type == RD_IN || var.cur->type == HERDC)
		{
			if (ft_add_redirecs(&var.cur, &var.redirects))
				ft_free_exit(var.cmd_head, (*dt)->lsttoken,
					(*dt)->env, var.args);
		}
		if (var.cur->type == PIPE || var.cur->next == NULL)
			ft_handle_new_command(&var, dt);
		var.cur = var.cur->next;
	}
	ft_free_double(var.args);
	return (ft_free_tokens((*dt)->lsttoken), var.cmd_head);
}
