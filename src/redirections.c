/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsylvant <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 18:00:43 by hsylvant          #+#    #+#             */
/*   Updated: 2022/09/28 18:00:45 by hsylvant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

static int	redirects_i_o_2(t_list *curr, int i, char **tokens);
static int	redirects_i_o_3(t_list *curr, int i, char **tokens);
static int	redirects_i_o_4(t_list *curr, int i, char **tokens);
static int	redirects_i_o_5(t_list *curr, int i, char **tokens);

/* Checks and makes changes if an output or input of a command
** should be redirected. */
int	redirects_i_o(t_list *curr, int i, char **tokens)
{
	int		err_num;

	err_num = SUCCESS;
	if (ft_strncmp(tokens[i], "<", 2) == 0)
		err_num = redirects_i_o_2(curr, i, tokens);
	else if (ft_strncmp(tokens[i], "<<", 3) == 0)
		err_num = redirects_i_o_3(curr, i, tokens);
	else if (ft_strncmp(tokens[i], ">", 2) == 0)
		err_num = redirects_i_o_4(curr, i, tokens);
	else if (ft_strncmp(tokens[i], ">>", 3) == 0)
		err_num = redirects_i_o_5(curr, i, tokens);
	return (err_num);
}

static int	redirects_i_o_2(t_list *curr, int i, char **tokens)
{
	char	*unquoted_token;

	if (curr->input != STDIN_FILENO && close(curr->input) == -1)
		return (FAILURE);
	unquoted_token = remove_quotes(tokens[i + 1]);
	curr->input = open(unquoted_token, O_RDONLY);
	free(unquoted_token);
	if (curr->input == -1 && curr->open_err == NULL)
	{
		curr->open_err = create_error_message(tokens[i + 1], errno);
		if (curr->open_err == NULL)
			return (FAILURE);
		g_status = GENERAL_ERR;
		curr->input = STDIN_FILENO;
	}
	return (SUCCESS);
}

static int	redirects_i_o_3(t_list *curr, int i, char **tokens)
{
	char	*unquoted_token;

	if (curr->input != STDIN_FILENO && close(curr->input) == -1)
		return (FAILURE);
	unquoted_token = remove_quotes(tokens[i + 1]);
	curr->input = get_here_doc_fd(unquoted_token);
	free(unquoted_token);
	if (curr->input == HERE_DOC_CTRL_C)
	{
		curr->input = -1;
		return (HERE_DOC_CTRL_C);
	}
	else if (curr->input == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	redirects_i_o_4(t_list *curr, int i, char **tokens)
{
	char	*unquoted_token;

	unquoted_token = remove_quotes(tokens[i + 1]);
	curr->output = open(unquoted_token, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	free(unquoted_token);
	if (curr->output == -1 && curr->open_err == NULL)
	{
		curr->open_err = create_error_message(tokens[i + 1], errno);
		if (curr->open_err == NULL)
			return (FAILURE);
		g_status = GENERAL_ERR;
		curr->output = STDOUT_FILENO;
	}
	return (SUCCESS);
}

static int	redirects_i_o_5(t_list *curr, int i, char **tokens)
{
	char	*unquoted_token;

	unquoted_token = remove_quotes(tokens[i + 1]);
	curr->output = open(unquoted_token,
			O_WRONLY | O_APPEND | O_CREAT, 0644);
	free(unquoted_token);
	if (curr->output == -1 && curr->open_err == NULL)
	{
		curr->open_err = create_error_message(tokens[i + 1], errno);
		if (curr->open_err == NULL)
			return (FAILURE);
		g_status = GENERAL_ERR;
		curr->output = STDOUT_FILENO;
	}
	return (SUCCESS);
}
