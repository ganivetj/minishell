/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:25:13 by hsylvant          #+#    #+#             */
/*   Updated: 2022/09/28 18:17:38 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_2(char *s1, char *s2)
{
	char	*ptr;
	int		i;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	i = 0;
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (0);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		++i;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		ptr[i + ft_strlen(s1)] = s2[i];
		i++;
	}
	ptr[i + ft_strlen(s1)] = '\0';
	return (ptr);
}

void	free_list_cmd(t_list *list)
{
	t_list	*curr;
	t_list	*free_cmd;
	char	**free_full_cmd;

	curr = list;
	while (curr != NULL)
	{
		if (curr->open_err != NULL)
		{
			free(curr->open_err);
			curr->open_err = NULL;
		}
		free_cmd = curr;
		free_full_cmd = curr->full_cmd;
		curr = curr->next_cmd;
		free(free_cmd);
		ft_free_2d_char_array(free_full_cmd);
	}
	list = NULL;
}

int	check_binary_file_access(char *path)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
			return (SUCCESS);
		else
			return (NO_PERMISSION);
	}
	return (CMD_NO_FND_ERR);
}

int	is_relative_or_absolute(char *path)
{
	int	i;

	i = 0;
	while (path[i] != '\0')
	{
		if (path[i] == '/')
			return (1);
		++i;
	}
	return (0);
}
