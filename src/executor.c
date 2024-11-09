/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsylvant <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 18:02:59 by hsylvant          #+#    #+#             */
/*   Updated: 2022/09/28 18:03:00 by hsylvant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(t_prompt **prompt);
static void	child_process_2(t_prompt **prompt);
static int	executor_2(t_prompt **prompt);

int	executor(t_prompt **prompt)
{
	t_list	*curr;
	int		wstatus;

	curr = (*prompt)->cmds;
	if (executor_2(prompt) == FAILURE)
		return (FAILURE);
	(*prompt)->cmds = curr;
	while (curr != NULL)
	{	
		if (curr->is_builtin == 0 && curr->open_err == NULL)
		{
			if (waitpid(curr->pid, &wstatus, 0) == -1)
				return (err_handler((*prompt)->cmds, FREE_LC, PERROR, GEN));
			if (WIFEXITED(wstatus))
			{
				g_status = WEXITSTATUS(wstatus);
				if (g_status == STOP_PROGRAM)
					return (err_handler((*prompt)->cmds, FREE_LC, PERROR, GEN));
			}
		}
		curr = curr->next_cmd;
	}
	err_handler((*prompt)->cmds, FREE_LIST_CMD, NULL, g_status);
	return (SUCCESS);
}

static int	executor_2(t_prompt **prompt)
{
	while ((*prompt)->cmds != NULL)
	{
		(*prompt)->cmds->is_builtin
			= execute_builtin((*prompt)->cmds, (*prompt)->env_list, 0);
		if ((*prompt)->cmds->is_builtin == -1)
			return (err_handler((*prompt)->cmds, FREE_ALL, EXIT, g_status));
		if (!(*prompt)->cmds->is_builtin && (*prompt)->cmds->open_err == NULL)
		{
			(*prompt)->cmds->pid = fork();
			if ((*prompt)->cmds->pid == -1)
				return (err_handler((*prompt)->cmds, FREE_ALL, PERROR, GEN));
			if ((*prompt)->cmds->pid == 0)
				child_process(prompt);
		}
		if ((*prompt)->cmds->open_err != NULL)
			ft_putendl_fd((*prompt)->cmds->open_err, 2);
		if ((*prompt)->cmds->input != STDIN_FILENO)
			if (close((*prompt)->cmds->input) == -1)
				return (err_handler((*prompt)->cmds, FREE_ALL, PERROR, GEN));
		if ((*prompt)->cmds->output != STDOUT_FILENO)
			if (close((*prompt)->cmds->output) == -1)
				return (err_handler((*prompt)->cmds, FREE_ALL, PERROR, GEN));
		(*prompt)->cmds = (*prompt)->cmds->next_cmd;
	}
	return (SUCCESS);
}

static void	child_process(t_prompt **prompt)
{
	int		err_num;

	err_num = create_full_path(prompt);
	if (err_num == FAILURE)
	{
		free(*prompt);
		exit (STOP_PROGRAM);
	}
	else if (err_num == FT_CONTINUE)
	{
		free(*prompt);
		exit (g_status);
	}
	child_process_2(prompt);
}

static void	child_process_2(t_prompt **prompt)
{
	t_list	*curr;
	char	**env;

	curr = (*prompt)->cmds;
	close_input(prompt, curr);
	close_output(prompt, curr);
	if (close_pipes(curr) == FAILURE)
	{
		err_handler((*prompt)->cmds, FREE_LIST_CMD_PATH, PERROR, GENERAL_ERR);
		free(*prompt);
		exit (g_status);
	}
	if (env_list_to_array(*prompt, &env) == FAILURE)
	{
		err_handler((*prompt)->cmds, FREE_LIST_CMD_PATH, PERROR, GENERAL_ERR);
		free(*prompt);
		exit (g_status);
	}
	execve(curr->full_path, curr->full_cmd, env);
	err_handler((*prompt)->cmds, FREE_LIST_CMD_PATH, PERROR, GENERAL_ERR);
	free(env);
	free(*prompt);
	exit (g_status);
}
