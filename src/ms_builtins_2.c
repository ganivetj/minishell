/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:44:22 by jganivet          #+#    #+#             */
/*   Updated: 2022/09/30 16:53:21 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_list	*get_smallest(t_env_list *head);
static void			print_ordered_list(t_list *curr, t_env_list *env_list);
static void			mark_all_zero(t_env_list *head);

int	ft_env(t_list *curr, t_env_list *env_list)
{
	t_env_list	*list_item;
	char		**pair;

	list_item = env_list->next;
	while (1)
	{
		pair = ft_split(list_item->value, '=');
		if (pair[1] || list_item->value[ft_strlen(list_item->value) - 1] == '=')
		{
			write(curr->output, list_item->value, ft_strlen(list_item->value));
			write(curr->output, "\n", 1);
		}
		if (pair[0])
			free(pair[0]);
		if (pair[1])
			free(pair[1]);
		free(pair);
		if (!list_item->next)
			break ;
		list_item = list_item->next;
	}
	return (0);
}

int	ft_export(t_list *curr, t_env_list *env_list)
{
	int	i;
	int	ret_val;

	ret_val = 0;
	if (!curr->full_cmd[1])
	{
		print_ordered_list(curr, env_list);
		return (0);
	}
	i = 1;
	while (curr->full_cmd[i])
	{
		if (checkvar(curr->full_cmd[i]))
			set_env_val(env_list, curr->full_cmd[i]);
		else
		{
			write(2, "minishell: export: `", 20);
			ft_putstr_fd(curr->full_cmd[i], 2);
			write(2, "\': not a valid identifier\n", 26);
			ret_val = 1;
		}
		++i;
	}
	return (ret_val);
}

void	print_ordered_list(t_list *curr, t_env_list *env_list)
{
	t_env_list	*smallest;
	char		**pair;

	mark_all_zero(env_list);
	while (1)
	{
		smallest = get_smallest(env_list);
		if (!smallest)
			break ;
		smallest->marked = 1;
		pair = ft_split(smallest->value, '=');
		write(curr->output, "declare -x ", 11);
		ft_putstr_fd(pair[0], curr->output);
		write(curr->output, "=\"", 2);
		if (pair[1])	
			ft_putstr_fd(pair[1], curr->output);
		write(curr->output, "\"", 1);
		write(curr->output, "\n", 1);
		free(pair[0]);
		free(pair[1]);
		free(pair);
	}
}

t_env_list	*get_smallest(t_env_list *head)
{
	t_env_list	*curr;
	t_env_list	*smallest;

	smallest = 0;
	curr = head->next;
	while (1)
	{
		if (curr->marked)
		{
			if (!curr->next)
				break ;
			curr = curr->next;
			continue ;
		}
		if (smallest == 0)
			smallest = curr;
		else if (ft_strcmp(curr->value, smallest->value) < 0)
			smallest = curr;
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	return (smallest);
}

static void	mark_all_zero(t_env_list *head)
{
	t_env_list	*curr;

	curr = head;
	while (1)
	{
		curr->marked = 0;
		if (!curr->next)
			break ;
		curr = curr->next;
	}
}
