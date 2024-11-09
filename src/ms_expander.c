/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:02:46 by jganivet          #+#    #+#             */
/*   Updated: 2022/09/27 16:54:57 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_all_vars(char *str, t_env_list *env_list_head);
static int	count_variables(char *str, int i, int v);
static char	*expand_first_var(char *str, t_env_list *env_list_head);
char		*return_expanded(char *str, t_env_list *env_list_head, int i);

int	expand_array(char **arry, t_env_list *env_list_head)
{
	int		i;
	char	*expanded_str;

	i = 0;
	while (arry[i])
	{
		expanded_str = expand_all_vars(arry[i], env_list_head);
		if (!expanded_str)
			return (1);
		if (expanded_str != arry[i])
		{
			free(arry[i]);
			arry[i] = expanded_str;
		}
		++i;
	}
	return (0);
}

static char	*expand_all_vars(char *str, t_env_list *env_list_head)
{
	int		v;
	int		i;
	char	*newstr;
	char	*trans;

	v = count_variables(str, 0, 0);
	if (v == 0)
		return (str);
	trans = ft_strdup(str);
	i = 0;
	while (i < v)
	{
		newstr = expand_first_var(trans, env_list_head);
		free(trans);
		trans = newstr;
		++i;
	}
	return (newstr);
}

static int	count_variables(char *str, int i, int v)
{
	char	split_char;

	v = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			split_char = str[i++];
			while (str[i] != '\0' && str[i] != split_char)
			{
				if (str[i] == '$' && split_char != '\''
					&& is_valid_variable(str, i))
					++v;
				++i;
			}
		}
		if (!str[i])
			break ;
		if (str[i] == '$' && is_valid_variable(str, i))
			++v;
		++i;
	}
	return (v);
}

static char	*expand_first_var(char *str, t_env_list *env_list_head)
{
	int		i;
	char	split_char;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			split_char = str[i];
			++i;
			while (str[i] != '\0' && str[i] != split_char)
			{
				if (str[i] == '$' && split_char != '\''
					&& is_valid_variable(str, i))
					return (return_expanded(str, env_list_head, i));
				++i;
			}
		}
		if (!str[i])
			break ;
		if (str[i] == '$' && is_valid_variable(str, i))
			return (return_expanded(str, env_list_head, i));
		++i;
	}
	return (0);
}

char	*return_expanded(char *str, t_env_list *env_list_head, int i)
{
	int		j;
	char	*newstr;

	j = i + 1;
	while (!is_stop_sign(str[j]))
		++j;
	if (str[i + 1] == '?' && is_stop_sign(str[i + 2]))
		++j;
	newstr = expand_var(i + 1, j, str, env_list_head);
	return (newstr);
}
