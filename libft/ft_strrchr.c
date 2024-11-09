/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:48:29 by jganivet          #+#    #+#             */
/*   Updated: 2021/11/03 16:06:41 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*latest_c;

	latest_c = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			latest_c = (char *)s + i;
		++i;
	}
	if (c == 0)
		return ((char *)s + i);
	else
		return (latest_c);
}
