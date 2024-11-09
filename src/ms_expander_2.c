/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:02:59 by jganivet          #+#    #+#             */
/*   Updated: 2022/09/27 16:53:02 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_stop_sign(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (0);
	return (1);
}

int	is_valid_variable(char *str, int i)
{
	if ((!is_stop_sign(str[i + 1]) && !ft_isdigit(str[i + 1]))
		|| (str[i + 1] == '?' && is_stop_sign(str[i + 2])))
		return (1);
	return (0);
}

char	*ft_quote(char *str)
{
	char	*newstr;
	size_t	i;

	newstr = malloc(ft_strlen(str) + 3);
	if (!newstr)
		return (0);
	newstr[0] = '"';
	i = 1;
	while (i < ft_strlen(str) + 1)
	{
		newstr[i] = str[i - 1];
		++i;
	}
	newstr[i] = '"';
	newstr[i + 1] = '\0';
	free(str);
	return (newstr);
}

char	*expand_var(int a, int b, char *str, t_env_list *env_list_head)
{
	char	*getenv_result;
	char	*newstr;
	char	*part1;
	char	*temp;

	newstr = 0;
	temp = ft_substr(str, a, b - a);
	if (!temp)
		return (0);
	getenv_result = get_env_val(env_list_head, temp);
	if (ft_strchr(getenv_result, '|') || ft_strchr(getenv_result, '<')
		|| ft_strchr(getenv_result, '>'))
		getenv_result = ft_quote(getenv_result);
	free(temp);
	if (!getenv_result)
		return (0);
	part1 = ft_substr(str, 0, a - 1);
	temp = ft_strjoin(part1, getenv_result);
	free(part1);
	part1 = ft_substr(str, b, ft_strlen(str) - b);
	newstr = ft_strjoin(temp, part1);
	free(part1);
	free(temp);
	free(getenv_result);
	return (newstr);
}
