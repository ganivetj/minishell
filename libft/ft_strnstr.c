/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:28:36 by jganivet          #+#    #+#             */
/*   Updated: 2021/11/22 10:14:24 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	int		i;
	int		j;
	int		nogood;

	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	if ((int)n < 0)
		n = ft_strlen(haystack);
	i = 0;
	while (i <= (int)(ft_strlen(haystack)
		- (int)ft_strlen(needle)) && i < (int)n)
	{
		j = 0;
		nogood = 0;
		while (j < (int)ft_strlen(needle))
		{
			if (*(haystack + i + j) != *(needle + j) || i + j >= (int)n)
				nogood = 1;
			++j;
		}
		if (nogood == 0)
			return ((char *)haystack + i);
		++i;
	}
	return ((char *)0);
}
