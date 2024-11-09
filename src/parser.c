/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsylvant <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 18:00:43 by hsylvant          #+#    #+#             */
/*   Updated: 2022/09/30 16:44:38 by hsylvant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parser_2(t_prompt **p, char **tokens, t_list *curr, t_list *list);
static int	create_cmd(t_list **curr, t_list *list, int i, char **tokens);
static int	fill_list(char **t, t_list *curr, t_list *list, t_container *x);

/* Iterates over the tokens array and creates the prompt structure */
int	parser(t_prompt **prompt, char **tokens)
{
	int		words;
	int		err_num;	
	t_list	*list;
	t_list	*curr;

	words = count_words_in_cmd(tokens);
	if (words == FT_CONTINUE)
	{
		err_handler(NULL, NO_FREE, NO_FILENAM, SYNTAX_ERR);
		return (FT_CONTINUE);
	}
	list = NULL;
	if (insert_cmd(&list) == FAILURE)
		return (err_handler(NULL, NO_FREE, PERROR, GENERAL_ERR));
	curr = list;
	curr->full_cmd = ft_calloc((words + 1), sizeof(char *));
	if (curr->full_cmd == NULL)
		return (err_handler(list, FREE_LIST, PERROR, GENERAL_ERR));
	err_num = parser_2(prompt, tokens, curr, list);
	return (err_num);
}

static int	parser_2(t_prompt **p, char **tokens, t_list *curr, t_list *list)
{
	t_container	x;
	int			err_num;

	x.i = 0;
	x.j = 0;
	err_num = fill_list(tokens, curr, list, &x);
	if (err_num == HERE_DOC_CTRL_C)
	{
		err_handler(list, FREE_ALL, NULL, GENERAL_ERR);
		return (FT_CONTINUE);
	}
	else if (err_num != SUCCESS)
	{
		err_handler(list, FREE_ALL, PERROR, GENERAL_ERR);
		return (err_num);
	}
	*p = malloc(sizeof(t_prompt));
	if (p == NULL)
		return (err_handler(list, FREE_ALL, PERROR, GENERAL_ERR));
	(*p)->cmds = list;
	return (SUCCESS);
}

/* Fills the linked list with all commands. */
static int	fill_list(char **t, t_list *curr, t_list *list, t_container *x)
{
	while (t[x->i] != NULL)
	{
		x->err_num = redirects_i_o(curr, x->i, t);
		if (x->err_num != SUCCESS)
			return (x->err_num);
		if (!ft_strncmp(t[x->i], "<", 2) || !ft_strncmp(t[x->i], "<<", 3)
			|| !ft_strncmp(t[x->i], ">", 2) || !ft_strncmp(t[x->i], ">>", 3))
			++(x->i);
		else if (ft_strncmp(t[x->i], "|", 2) == 0)
		{
			g_status = 0;
			x->err_num = create_cmd(&curr, list, x->i, t);
			if (x->err_num != SUCCESS)
				return (x->err_num);
			x->j = 0;
		}
		else
		{
			curr->full_cmd[(x->j)++] = remove_quotes(t[x->i]);
			if (curr->full_cmd[x->j - 1] == NULL)
				return (FAILURE);
		}
		++(x->i);
	}
	return (SUCCESS);
}

/* This function creates new commands after a '|' and redirects the pipes */
static int	create_cmd(t_list **curr, t_list *list, int i, char **tokens)
{
	int	words;

	if (insert_cmd(curr) == FAILURE)
		return (err_handler(list, FREE_ALL, PERROR, GENERAL_ERR));
	if (pipe((*curr)->pipes) == -1)
		return (err_handler(list, FREE_ALL, PERROR, GENERAL_ERR));
	(*curr)->next_cmd->input = (*curr)->pipes[READ_END];
	if ((*curr)->output == STDOUT_FILENO)
		(*curr)->output = (*curr)->pipes[WRITE_END];
	else if (close((*curr)->pipes[WRITE_END]) == -1)
		return (err_handler(list, FREE_ALL, PERROR, GENERAL_ERR));
	words = count_words_in_cmd(tokens + i + 1);
	if (words == FT_CONTINUE)
	{
		err_handler(list, FREE_ALL, NO_FILENAM, SYNTAX_ERR);
		return (FT_CONTINUE);
	}
	*curr = (*curr)->next_cmd;
	(*curr)->full_cmd = ft_calloc((words + 1), sizeof(char *));
	if ((*curr)->full_cmd == NULL)
		return (err_handler(list, FREE_ALL, PERROR, GENERAL_ERR));
	return (SUCCESS);
}

char	*create_error_message(char *token, int err_number)
{
	char	*aux_str;
	char	*error_message;

	error_message = ft_strjoin("-minishell: ", token);
	if (error_message == NULL)
		return (NULL);
	aux_str = ft_strjoin(error_message, ": ");
	free(error_message);
	if (aux_str == NULL)
		return (NULL);
	error_message = ft_strjoin(aux_str, strerror(err_number));
	free(aux_str);
	if (error_message == NULL)
		return (NULL);
	return (error_message);
}
