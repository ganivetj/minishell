/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:39:37 by jganivet          #+#    #+#             */
/*   Updated: 2021/11/22 09:59:33 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	offset;

	offset = 0;
	if (dstsize > 0)
	{
		while (*(src + offset) != '\0')
		{
			if (offset == dstsize - 1)
				break ;
			*(dst + offset) = *(src + offset);
			offset++;
		}
		*(dst + offset) = '\0';
	}
	while (*(src + offset) != '\0')
		offset++;
	return (offset);
}
