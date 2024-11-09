/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:36:18 by jganivet          #+#    #+#             */
/*   Updated: 2021/11/18 16:32:52 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	int		d_len;
	int		offset;
	int		src_index;

	d_len = ft_strlen(dst);
	offset = d_len;
	src_index = 0;
	if ((int)dstsize < 0)
		dstsize = 2147483647;
	while (*(src + src_index) != '\0'
		&& (src_index < (int)dstsize - d_len - 1))
	{
		*(dst + offset) = *(src + src_index);
		++offset;
		++src_index;
	}
	if (!(dstsize == 0) || d_len <= (int)dstsize)
		*(dst + offset) = '\0';
	if (d_len < (int)dstsize)
		return (ft_strlen(src) + d_len);
	else
		return (ft_strlen(src) + dstsize);
}
