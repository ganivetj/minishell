/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsylvant <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 18:03:14 by hsylvant          #+#    #+#             */
/*   Updated: 2022/09/28 18:03:16 by hsylvant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	remove_quotes_2(char *token, char *quote_char, t_container *x);

/* Counts the number of words in the command. */
int	count_words_in_cmd(char **tokens)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (tokens[i] != NULL && ft_strncmp(tokens[i], "|", 2) != 0)
	{
		if ((ft_strncmp(tokens[i], "<", 2) != 0)
			&& (ft_strncmp(tokens[i], ">", 2) != 0)
			&& (ft_strncmp(tokens[i], "<<", 3) != 0)
			&& (ft_strncmp(tokens[i], ">>", 3) != 0))
			++words;
		else
		{
			++i;
			if (tokens[i] == NULL || ft_strncmp(tokens[i], "|", 2) == 0)
				return (FT_CONTINUE);
		}
		++i;
	}
	return (words);
}

/* Inserts a new node/command to the linked list. */
int	insert_cmd(t_list **curr)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return (FAILURE);
	new_node->next_cmd = NULL;
	new_node->full_cmd = NULL;
	new_node->input = STDIN_FILENO;
	new_node->output = STDOUT_FILENO;
	new_node->open_err = NULL;
	if (*curr == NULL)
		*curr = new_node;
	else
		(*curr)->next_cmd = new_node;
	return (SUCCESS);
}

char	*remove_quotes(char *token)
{
	t_container	x;
	int			j;
	char		*str;
	char		quote_char;

	str = malloc(sizeof_str(token) * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	x.i = 0;
	j = 0;
	quote_char = 0;
	while (token[x.i] != '\0')
	{
		if (remove_quotes_2(token, &quote_char, &x) == FT_CONTINUE)
			continue ;
		str[j] = token[x.i];
		++j;
		++(x.i);
	}
	str[j] = '\0';
	return (str);
}

static int	remove_quotes_2(char *token, char *quote_char, t_container *x)
{
	if ((token[x->i] == '\'' && *quote_char == 0)
		|| (token[x->i] == '"' && *quote_char == 0))
	{
		*quote_char = token[x->i];
		++(x->i);
	}
	if (token[x->i] == *quote_char)
	{
		*quote_char = 0;
		++(x->i);
		return (FT_CONTINUE);
	}
	return (SUCCESS);
}

int	sizeof_str(char *token)
{
	int		size;
	int		i;
	char	quote_char;

	size = 0;
	i = 0;
	quote_char = 0;
	while (token[i] != '\0')
	{
		if ((token[i] == '\'' && quote_char == 0)
			|| (token[i] == '"' && quote_char == 0))
		{
			quote_char = token[i];
			++i;
		}
		if (token[i] == quote_char)
		{
			quote_char = 0;
			++i;
			continue ;
		}
		++size;
		++i;
	}
	return (size);
}
