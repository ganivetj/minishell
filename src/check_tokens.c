/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:05:33 by hsylvant          #+#    #+#             */
/*   Updated: 2022/09/30 15:57:15 by hsylvant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	manage_err(int syntax);

int	check_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (ft_strncmp(tokens[i], "|", 2) == 0)
		return (manage_err(1));
	while (tokens[i] != NULL)
	{
		if (tokens[i][0] == '>' || tokens[i][0] == '<')
		{
			if (tokens[i + 1] != NULL
				&& (tokens[i + 1][0] == '<' || tokens[i + 1][0] == '>'))
				return (manage_err(2));
		}
		else if (ft_strncmp(tokens[i], "|", 2) == 0)
		{
			if (tokens[i + 1] != NULL && ft_strncmp(tokens[i + 1], "|", 2) == 0)
				return (manage_err(1));
		}
		++i;
	}
	if (ft_strncmp(tokens[i - 1], "|", 2) == 0)
		return (manage_err(1));
	return (SUCCESS);
}

static int	manage_err(int syntax)
{
	if (syntax == 1)
	{
		err_handler(NULL, NO_FREE, SYNTAX_1, SYNTAX_ERR);
		return (FT_CONTINUE);
	}
	if (syntax == 2)
	{
		err_handler(NULL, NO_FREE, SYNTAX_2, SYNTAX_ERR);
		return (FT_CONTINUE);
	}
	return (0);
}
