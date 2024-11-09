/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:40:02 by jganivet          #+#    #+#             */
/*   Updated: 2022/10/03 12:09:31 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			ft_unset2(t_env_list *env, char *cmd);
static void			freedata(t_env_list *curr, char *key);

int	ft_unset(t_list *s_list, t_env_list *env_list)
{
	int	i;
	int	ret_val;

	ret_val = 0;
	i = 1;
	while (s_list->full_cmd[i])
	{
		if (*(s_list->full_cmd[i]))
			ft_unset2(env_list, s_list->full_cmd[i]);
		else
		{
			write(2, "minishell: unset: `", 20);
			write(2, "\': not a valid identifier\n", 26);
			ret_val = 1;
		}
		++i;
	}
	return (ret_val);
}

int	ft_unset2(t_env_list *env_list, char *cmd)
{
	t_env_list	*curr;
	t_env_list	*prev;
	char		*key;

	prev = env_list;
	curr = env_list->next;
	while (1)
	{
		key = getkey(curr->value);
		if (!ft_strncmp(cmd, key,
				ft_strlen(key) + 1))
		{
			prev->next = curr->next;
			freedata(curr, key);
			break ;
		}
		free(key);
		if (curr->next == 0)
			break ;
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

void	freedata(t_env_list *curr, char *key)
{
	free(curr->value);
	free(curr);
	free(key);
	return ;
}
