/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:18:23 by jganivet          #+#    #+#             */
/*   Updated: 2022/09/28 15:19:15 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_struct(t_list *list, int to_free);

int	err_handler(t_list *list, int to_free, char *err_msg, int err_num)
{
	g_status = err_num;
	if (err_msg != NULL)
	{
		if (ft_strncmp(err_msg, IS_DIR, ft_strlen(err_msg) + 1) == 0)
			ft_putendl_fd(err_msg, 2);
		else if (err_num == NO_PERMISSION)
		{
			ft_putstr_fd("-minishell: ", 2);
			perror(list->full_path);
		}
		else if (ft_strncmp(err_msg, PERROR, ft_strlen(err_msg) + 1) == 0)
			perror("-minishell");
		else if (ft_strncmp(err_msg, PERROR_2, ft_strlen(err_msg) + 1) == 0)
		{
			ft_putstr_fd("-minishell: ", 2);
			perror(list->full_path);
		}
		else
			ft_putendl_fd(err_msg, 2);
	}
	if (to_free != NO_FREE)
		free_struct(list, to_free);
	return (FAILURE);
}

static void	free_struct(t_list *list, int to_free)
{
	if (to_free == FREE_LIST)
		free(list);
	else if (to_free == FREE_LIST_CMD)
		free_list_cmd(list);
	else if (to_free == FREE_ALL)
	{
		close_pipes(list);
		free_list_cmd(list);
	}
	else if (to_free == FREE_ALL_PATH)
	{
		close_pipes(list);
		free(list->full_path);
		free_list_cmd(list);
	}
	else if (to_free == FREE_LIST_CMD_PATH)
	{
		free(list->full_path);
		free_list_cmd(list);
	}
}
