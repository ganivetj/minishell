/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:53:57 by jganivet          #+#    #+#             */
/*   Updated: 2022/09/30 14:31:19 by hsylvant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void					freedata(char **pair);
static struct s_env_list	*get_last_node(struct s_env_list *head);

struct s_env_list	*cpy_envp_to_env_list(char **envp)
{
	int					i;
	struct s_env_list	*env_list_head;
	struct s_env_list	*new;
	struct s_env_list	*prev;

	env_list_head = malloc(sizeof(t_env_list));
	if (!env_list_head || !envp[0])
		return (0);
	env_list_head->next = NULL;
	env_list_head->value = NULL;
	i = 0;
	while (envp[i])
	{
		prev = get_last_node(env_list_head);
		new = malloc(sizeof(t_env_list));
		if (new == NULL)
			return (0);
		new->value = ft_strdup(envp[i]);
		new->next = 0;
		prev->next = new;
		++i;
	}
	return (env_list_head);
}

struct s_env_list	*get_last_node(struct s_env_list *head)
{
	struct s_env_list	*curr;

	curr = head;
	while (curr->next)
		curr = curr->next;
	return (curr);
}

char	*get_env_val(struct s_env_list *head, char *key)
{
	t_env_list	*curr;
	char		**pair;
	char		*ret;

	if (key[0] == '?' && !key[1])
		return (ft_itoa(g_status));
	curr = head->next;
	while (1)
	{
		pair = ft_split(curr->value, '=');
		if (!ft_strncmp(pair[0], key, ft_strlen(pair[0]) + 1))
		{
			if (pair[1])
				ret = ft_strdup(pair[1]);
			else
				ret = ft_calloc(1, 1);
			freedata(pair);
			return (ret);
		}
		freedata(pair);
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	return (ft_calloc(1, 1));
}

void	freedata(char	**pair)
{
	int	i;

	i = 0;
	while (pair[i])
	{
		free(pair[i]);
		++i;
	}
	free(pair);
}

int	free_env_list(t_env_list *head)
{
	t_env_list	*curr;
	t_env_list	*next;

	curr = head;
	next = 0;
	while (1)
	{
		if (curr->value)
			free(curr->value);
		next = curr->next;
		free(curr);
		curr = next;
		if (next == 0)
			break ;
	}
	return (0);
}
