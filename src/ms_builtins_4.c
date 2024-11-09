/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:44:22 by jganivet          #+#    #+#             */
/*   Updated: 2022/09/30 15:27:42 by hsylvant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exit2(t_list *curr);

int	ft_exit(t_list *curr)
{
	g_status = 0;
	if (curr->full_cmd[1] && curr->full_cmd[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		g_status = 1;
		return (1);
	}
	if (curr->full_cmd[1])
		ft_exit2(curr);
	if (curr->input != STDIN_FILENO || curr->output != STDOUT_FILENO)
		return (1);
	return (0);
}

void	ft_exit2(t_list *curr)
{	
	int	i;

	i = 0;
	g_status = ft_atoi(curr->full_cmd[1]);
	while (curr->full_cmd[1][i])
	{
		if (!ft_isdigit(curr->full_cmd[1][i]))
		{
			write(2, "minishell: exit: ", 17);
			ft_putstr_fd(curr->full_cmd[1], 2);
			write(2, ": numeric argument required\n", 28);
			g_status = 255;
			break ;
		}
		++i;
	}	
}

int	ft_pwd(t_list *curr)
{
	char	cwd[256];

	getcwd(cwd, 256);
	write(curr->output, &cwd, ft_strlen(cwd));
	write(curr->output, "\n", 1);
	return (0);
}
