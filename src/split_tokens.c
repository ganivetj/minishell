/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:35:04 by hsylvant          #+#    #+#             */
/*   Updated: 2022/09/30 15:26:54 by hsylvant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_array_size(char *s);
static int	ft_chunk_size(char *s);
static char	**ft_recursion(char **array, char *s, int flag);

/* The function checks first the array size to allocate memory.
** Then it uses recursion to fill the array. */
int	split_tokens(char ***tokens, char **s)
{
	int		flag;
	int		array_size;
	int		i;

	i = 0;
	while (ft_isspace((*s)[i]))
		++i;
	if ((*s)[i] == '\0')
		return (FT_CONTINUE);
	array_size = ft_check_array_size(*s);
	if (array_size == FT_CONTINUE)
	{
		err_handler(NULL, NO_FREE, QUOTES, GENERAL_ERR);
		return (FT_CONTINUE);
	}
	*tokens = ft_calloc(array_size, sizeof(char *));
	if (*tokens == NULL)
		return (err_handler(NULL, NO_FREE, PERROR, GENERAL_ERR));
	flag = 0;
	*tokens = ft_recursion(*tokens, *s, flag);
	if (*tokens == NULL)
		return (FAILURE);
	return (SUCCESS);
}

static int	ft_check_array_size(char *s)
{
	int	i;
	int	array_size;
	int	chunk_size;

	i = 0;
	array_size = 0;
	while (s[i] != '\0')
	{
		while (ft_isspace(s[i]))
			++i;
		chunk_size = ft_chunk_size(s + i);
		if (chunk_size == FT_CONTINUE)
			return (FT_CONTINUE);
		i = i + chunk_size;
		++array_size;
	}
	if (s[i - 1] != ' ')
		++array_size;
	return (array_size);
}

static int	ft_chunk_size(char *s)
{
	int		i;
	char	split_char;

	i = 0;
	while (!ft_isspace(s[i]) && s[i] != '\0'
		&& s[i] != '|' && s[i] != '<' && s[i] != '>')
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			split_char = s[i];
			++i;
			while (s[i] != '\0' && s[i] != split_char)
				++i;
			if (s[i] == '\0')
				return (FT_CONTINUE);
		}
		++i;
	}
	if (s[0] == '|' || s[0] == '<' || s[0] == '>')
		++i;
	if (s[i - 1] == '<' && s[i] == '<')
			++i;
	else if (s[i - 1] == '>' && s[i] == '>')
			++i;
	return (i);
}

static char	**ft_recursion(char **array, char *s, int flag)
{
	int	i;
	int	chunk_size;

	i = 0;
	while (ft_isspace(s[i]))
		++i;
	if (ft_strlen(s + i) == 0)
	{
		array[flag] = NULL;
		return (array);
	}
	chunk_size = ft_chunk_size(s + i);
	array[flag] = ft_substr(s + i, 0, chunk_size);
	if (array[flag] == NULL)
	{
		ft_free_2d_char_array(array);
		err_handler(NULL, NO_FREE, PERROR, GENERAL_ERR);
		return (NULL);
	}
	++flag;
	array = ft_recursion(array, (s + i + chunk_size), flag);
	return (array);
}
