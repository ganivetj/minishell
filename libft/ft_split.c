/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:37:44 by jganivet          #+#    #+#             */
/*   Updated: 2021/11/18 11:44:59 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cc(char const *str, char c);
static int	pop(char const *s, char c, char **arry);

char	**ft_split(char const *s, char c)
{
	char	**arry;
	int		r;
	int		i;

	if (s == 0)
		return (NULL);
	arry = malloc((cc(s, c) + 1) * sizeof(char *));
	if (arry == NULL)
		return (NULL);
	arry[cc(s, c)] = NULL;
	r = pop(s, c, arry);
	if (r)
	{
		i = 0;
		while (i < r - 1)
			free(arry[i++]);
		free(arry);
		return (NULL);
	}
	return (arry);
}

static int	pop(char const *s, char c, char **arry)
{
	size_t	pos;
	int		s_idx;

	pos = 0;
	s_idx = 0;
	while (ft_strlen(s))
	{
		if (s[pos] == c || s[pos] == '\0')
		{
			if (pos > 0)
			{
				arry[s_idx] = malloc((pos + 1) * sizeof(char));
				if (arry[s_idx] == NULL)
					return (1 + s_idx);
				ft_strlcpy(arry[s_idx++], s, pos + 1);
				if (ft_strlen(s) <= 1 || cc(s, c) == 1 || s[pos] == '\0')
					return (0);
			}
			s += pos + 1;
			pos = -1;
		}
		++pos;
	}
	return (0);
}

static int	cc(char const *str, char c)
{
	size_t	i;
	int		chunks;

	chunks = 0;
	i = 1;
	while (i <= ft_strlen(str))
	{
		if (str[i - 1] != c)
		{
			if (str[i] == c || str[i] == '\0')
				++chunks;
		}
		++i;
	}
	return (chunks);
}
