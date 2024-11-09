/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:53:57 by jganivet          #+#    #+#             */
/*   Updated: 2022/09/30 10:15:19 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_list	*add_node(char *value);

int	set_env_val(struct s_env_list *head, char *val)
{
	t_env_list	*curr;
	char		*search_key;
	char		*curr_env_key;

	search_key = getkey(val);
	curr = head->next;
	while (1)
	{
		curr_env_key = getkey(curr->value);
		if (!ft_strncmp(curr_env_key, search_key, ft_strlen(curr_env_key) + 1))
		{
			free(curr_env_key);
			free(curr->value);
			curr->value = ft_strdup(val);
			free(search_key);
			return (0);
		}
		free(curr_env_key);
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	free(search_key);
	curr->next = add_node(ft_strdup(val));
	return (0);
}

t_env_list	*add_node(char *value)
{
	t_env_list	*newnode;

	newnode = malloc(sizeof(t_env_list));
	if (!newnode)
		return (0);
	newnode->value = value;
	newnode->next = 0;
	return (newnode);
}

char	*getkey(char *value)
{
	int		i;
	char	*key;

	if (value == NULL)
		return (0);
	i = 0;
	while (value[i] != '=' && value[i] != 0)
		++i;
	key = ft_substr(value, 0, i);
	return (key);
}

int	checkvar(char *val)
{
	int	i;

	i = 0;
	if (!ft_isalpha(val[0]) && val[0] != '_')
		return (0);
	while (1)
	{
		if ((val[i] == '=' || val[i] == 0) && i > 0)
			return (1);
		if ((val[i] == '=' || val[i] == 0) && i == 0)
			return (0);
		if (is_stop_sign(val[i]) && val[i] != '_')
			return (0);
		++i;
	}
	return (0);
}
