/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsylvant <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:30:11 by hsylvant          #+#    #+#             */
/*   Updated: 2022/09/30 14:30:13 by hsylvant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_path_2(int i, char *path, char **paths, t_prompt **prompt);
int	find_path_3(char ***paths, t_prompt **prompt);

int	find_path(t_prompt **prompt)
{
	int		err_num;
	int		i;
	char	*path;
	char	**paths;

	if (find_path_3(&paths, prompt) == FAILURE)
		return (FAILURE);
	i = 0;
	path = (*prompt)->cmds->full_path;
	while (paths[i] != NULL)
	{
		err_num = find_path_2(i, path, paths, prompt);
		if (err_num != FT_CONTINUE_2)
			return (err_num);
		free((*prompt)->cmds->full_path);
		++i;
	}
	ft_free_2d_char_array(paths);
	ft_putstr_fd(path + 1, 2);
	free(path);
	if (i == 0)
		err_handler((*prompt)->cmds, FREE_ALL, NO_FILE, CMD_NO_FND_ERR);
	else
		err_handler((*prompt)->cmds, FREE_ALL, CMD_NO_FND, CMD_NO_FND_ERR);
	return (FT_CONTINUE);
}

int	find_path_3(char ***paths, t_prompt **prompt)
{
	char	*path_env;

	path_env = get_env_val((*prompt)->env_list, "PATH");
	if (path_env == NULL)
		return (err_handler((*prompt)->cmds, FREE_ALL, NO_PATH, GENERAL_ERR));
	*paths = ft_split(path_env, ':');
	free(path_env);
	if (paths == NULL)
		return (err_handler((*prompt)->cmds, FREE_ALL_PATH, PERROR,
				GENERAL_ERR));
	return (SUCCESS);
}

int	find_path_2(int i, char *path, char **paths, t_prompt **prompt)
{
	(*prompt)->cmds->full_path = ft_strjoin_2(paths[i], path);
	if ((*prompt)->cmds->full_path == NULL)
	{
		free(path);
		ft_free_2d_char_array(paths);
		return (err_handler((*prompt)->cmds, FREE_ALL, PERROR,
				GENERAL_ERR));
	}
	if (check_binary_file_access((*prompt)->cmds->full_path)
		== NO_PERMISSION)
	{
		free(path);
		ft_free_2d_char_array(paths);
		err_handler((*prompt)->cmds, FREE_ALL_PATH, PERROR, NO_PERMISSION);
		return (FT_CONTINUE);
	}
	else if (check_binary_file_access((*prompt)->cmds->full_path)
		== SUCCESS)
	{
		free(path);
		ft_free_2d_char_array(paths);
		return (SUCCESS);
	}
	return (FT_CONTINUE_2);
}
