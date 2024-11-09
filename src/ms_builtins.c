/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:53:57 by jganivet          #+#    #+#             */
/*   Updated: 2022/09/30 13:38:23 by hsylvant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_echo_printloop(t_list *curr, int i);

int	execute_builtin(t_list *curr, t_env_list *env_list, int ret_val)
{
	if (curr->full_cmd[0] == NULL)
		return (SUCCESS);
	if (!ft_strncmp(curr->full_cmd[0], "echo", 5))
		ret_val = ft_echo(curr);
	else if (!ft_strncmp(curr->full_cmd[0], "cd", 3))
		ret_val = ft_cd(curr, env_list);
	else if (!ft_strncmp(curr->full_cmd[0], "pwd", 4))
		ret_val = ft_pwd(curr);
	else if (!ft_strncmp(curr->full_cmd[0], "env", 4))
		ret_val = ft_env(curr, env_list);
	else if (!ft_strncmp(curr->full_cmd[0], "export", 7))
		ret_val = ft_export(curr, env_list);
	else if (!ft_strncmp(curr->full_cmd[0], "unset", 6))
		ret_val = ft_unset(curr, env_list);
	else if (!ft_strncmp(curr->full_cmd[0], "exit", 5))
	{
		if (!ft_exit(curr))
			return (-1);
		else
			return (1);
	}
	else
		return (0);
	g_status = ret_val;
	return (1);
}

int	ft_echo(t_list *curr)
{
	int	opt_n;
	int	i;

	opt_n = 0;
	if (!curr->full_cmd[1])
	{
		write(curr->output, "\n", 1);
		return (0);
	}
	i = 1;
	while (curr->full_cmd[i] && !ft_strncmp(curr->full_cmd[i], "-n", 3))
	{
		opt_n = 1;
		++i;
	}
	if (!curr->full_cmd[i])
		return (0);
	ft_echo_printloop(curr, i);
	if (!opt_n)
		write(curr->output, "\n", 1);
	return (0);
}

void	ft_echo_printloop(t_list *curr, int i)
{
	while (curr->full_cmd[i])
	{
		write(curr->output, curr->full_cmd[i], ft_strlen(curr->full_cmd[i]));
		if (curr->full_cmd[i + 1])
			write(curr->output, " ", 1);
		++i;
	}
}
