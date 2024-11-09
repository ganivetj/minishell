/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:52:36 by jganivet          #+#    #+#             */
/*   Updated: 2021/11/22 10:01:20 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start < 0)
		start = 0;
	if (start >= ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	r = malloc(len + 1);
	if (r == 0)
		return (NULL);
	i = 0;
	while (s[i] && i < len)
	{
		*(r + i) = *(s + start + i);
		++i;
	}
	*(r + i) = '\0';
	return (r);
}
