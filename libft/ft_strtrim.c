/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:05:07 by jganivet          #+#    #+#             */
/*   Updated: 2021/11/22 10:01:09 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isinset(char c, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	int			start_point;
	int			end_point;
	int			i;
	char		*r;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start_point = 0;
	while (isinset(s1[start_point], set))
		++start_point;
	end_point = ft_strlen(s1) - 1;
	while (end_point > start_point && isinset(s1[end_point], set))
		--end_point;
	r = malloc(end_point - start_point + 2);
	if (r == NULL)
		return (NULL);
	i = 0;
	while (i < end_point - start_point + 1)
	{
		r[i] = s1[i + start_point];
		++i;
	}
	r[i] = '\0';
	return (r);
}

static int	isinset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(set))
	{
		if (set[i] == c)
			return (1);
		++i;
	}
	return (0);
}
