/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 12:05:29 by jganivet          #+#    #+#             */
/*   Updated: 2021/11/22 10:00:20 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*s2;

	if (s == NULL)
		return (0);
	s2 = malloc(ft_strlen(s) + 1);
	if (s2 == NULL)
		return (s2);
	i = 0;
	while (i < ft_strlen(s))
	{
		s2[i] = (*f)(i, s[i]);
		++i;
	}
	s2[i] = 0;
	return (s2);
}
