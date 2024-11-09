/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 14:34:42 by jganivet          #+#    #+#             */
/*   Updated: 2021/11/18 13:25:05 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		str_len;
	char	*ptr;
	int		i;

	str_len = ft_strlen(s1);
	ptr = malloc(str_len + 1);
	if (ptr == 0)
		return (0);
	i = 0;
	while (i <= str_len)
	{
		ptr[i] = s1[i];
		++i;
	}
	return (ptr);
}
