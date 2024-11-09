/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsylvant <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 18:02:54 by hsylvant          #+#    #+#             */
/*   Updated: 2022/09/28 18:02:56 by hsylvant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_full_path_2(t_prompt **prompt, t_list *curr);

int	create_full_path(t_prompt **prompt)
{
	t_list	*curr;
	int		err_num;

	curr = (*prompt)->cmds;
	if (curr->full_cmd[0] == NULL)
		return (FT_CONTINUE);
	else
	{
		err_num = create_full_path_2(prompt, curr);
		if (err_num != SUCCESS)
			return (err_num);
	}
	err_num = path_is_directory(curr->full_path);
	if (err_num == 1)
	{
		ft_putstr_fd("-minishell: ", 2);
		ft_putstr_fd(curr->full_path, 2);
		err_handler((*prompt)->cmds, FREE_ALL_PATH, IS_DIR, NO_PERMISSION);
		return (FT_CONTINUE);
	}
	else if (err_num == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	create_full_path_2(t_prompt **prompt, t_list *curr)
{
	int	err_num;

	if (is_relative_or_absolute(curr->full_cmd[0]) == 0)
	{
		curr->full_path = ft_strjoin_2("/", curr->full_cmd[0]);
		if (curr->full_path == NULL)
			return (err_handler((*prompt)->cmds, FREE_ALL, PERROR, GEN));
		return (find_path(prompt));
	}
	else
	{
		curr->full_path = ft_strdup(curr->full_cmd[0]);
		if (curr->full_path == NULL)
			return (err_handler((*prompt)->cmds, FREE_ALL, PERROR_2, GEN));
		err_num = check_binary_file_access(curr->full_path);
		if (err_num != SUCCESS)
		{
			err_handler((*prompt)->cmds, FREE_ALL_PATH, PERROR_2, err_num);
			return (FT_CONTINUE);
		}
	}
	return (SUCCESS);
}

int	close_pipes(t_list *list)
{
	while (list != NULL)
	{
		if (list->input != STDIN_FILENO && list->input != -1)
		{
			if (close(list->input) == -1)
			{
				list->input = -1;
				close_pipes(list);
				return (FAILURE);
			}
		}
		if (list->output != STDOUT_FILENO && list->output != -1)
		{
			if (close(list->output) == -1)
			{
				list->output = -1;
				close_pipes(list->next_cmd);
				return (FAILURE);
			}
		}
		list = list->next_cmd;
	}
	return (SUCCESS);
}

int	env_list_to_array(t_prompt *prompt, char ***env)
{
	int			i;
	t_env_list	*curr;

	i = 0;
	if (prompt->env_list == NULL)
		return (SUCCESS);
	curr = (prompt->env_list)->next;
	while (curr != NULL)
	{
		++i;
		curr = curr->next;
	}
	*env = malloc((i + 1) * sizeof(char *));
	if (*env == NULL)
		return (FAILURE);
	curr = (prompt->env_list)->next;
	i = 0;
	while (curr != NULL)
	{
		(*env)[i] = curr->value;
		++i;
		curr = curr->next;
	}
	(*env)[i] = NULL;
	return (SUCCESS);
}
