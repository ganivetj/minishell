/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:17:36 by jganivet          #+#    #+#             */
/*   Updated: 2022/09/27 15:22:23 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cd_printerr(char *target_dir);
static int	ft_cd2(t_list *curr, t_env_list *env_list, char *target_dir);

int	ft_cd(t_list *curr, t_env_list *env_list)
{
	char	*target_dir;

	if (!curr->full_cmd[1] || (curr->full_cmd[1][0] == '~'
		&& curr->full_cmd[1][1] == '\0'))
		target_dir = get_env_val(env_list, "HOME");
	else
		target_dir = curr->full_cmd[1];
	if (!target_dir[0])
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (1);
	}
	return (ft_cd2(curr, env_list, target_dir));
}	

static int	ft_cd2(t_list *curr, t_env_list *env_list, char *target_dir)
{	
	int		ret_val;
	char	*cwd_val;
	char	cwd[256];

	ret_val = chdir(target_dir);
	if (ret_val)
	{
		ft_cd_printerr(target_dir);
		ret_val = 1;
	}
	getcwd(cwd, 256);
	cwd_val = ft_strjoin("PWD=", cwd);
	set_env_val(env_list, cwd_val);
	free(cwd_val);
	if (!(target_dir == curr->full_cmd[1]))
		free(target_dir);
	return (ret_val);
}

void	ft_cd_printerr(char *target_dir)
{
	write(2, "minishell: cd: ", 15);
	ft_putstr_fd(target_dir, 2);
	write(2, ": No such file or directory\n", 28);
}
