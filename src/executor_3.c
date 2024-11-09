/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsylvant <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 18:02:59 by hsylvant          #+#    #+#             */
/*   Updated: 2022/09/28 18:03:00 by hsylvant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_input(t_prompt **prompt, t_list *curr)
{
	if (curr->input != STDIN_FILENO)
	{
		if (dup2(curr->input, STDIN_FILENO) == -1)
		{
			err_handler((*prompt)->cmds, FREE_ALL_PATH, PERROR, GENERAL_ERR);
			free(*prompt);
			exit (g_status);
		}
		if (close(curr->input) == -1)
		{
			curr->input = -1;
			free((*prompt)->cmds->full_path);
			err_handler((*prompt)->cmds, FREE_ALL, PERROR, GENERAL_ERR);
			free(*prompt);
			exit (g_status);
		}
		curr->input = -1;
	}
}

void	close_output(t_prompt **prompt, t_list *curr)
{
	if (curr->output != STDOUT_FILENO)
	{
		if (dup2(curr->output, STDOUT_FILENO) == -1)
		{
			free((*prompt)->cmds->full_path);
			err_handler((*prompt)->cmds, FREE_ALL, PERROR, GENERAL_ERR);
			free(*prompt);
			exit (g_status);
		}
		if (close(curr->output) == -1)
		{
			err_handler((*prompt)->cmds, FREE_ALL_PATH, PERROR, GENERAL_ERR);
			free(*prompt);
			exit (g_status);
		}
		curr->output = -1;
	}
}
