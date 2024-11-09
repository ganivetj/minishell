/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 11:07:50 by jganivet          #+#    #+#             */
/*   Updated: 2021/11/19 16:21:08 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_pow(int base, int exp);
int			ft_isspace(int c);  // Remove static, match the signature in libft.h
static int	find_start_point(const char *str);

int	ft_atoi(const char *str)
{
	int	sign_present;
	int	i;
	int	j;
	int	r;
	int	start_point;

	start_point = find_start_point(str);
	sign_present = (str[start_point] == '-' || str[start_point] == '+');
	i = sign_present;
	while (ft_isdigit(str[start_point + i]))
		++i;
	if (i > 19 && str[start_point] != '-')
		return (-1);
	else if (i > 19)
		return (0);
	r = 0;
	j = start_point + sign_present;
	while (j < start_point + i)
	{
		r = r + (str[j] - 48) * (ft_pow(10, start_point + i - j - 1));
		++j;
	}
	if (str[start_point] == '-')
		r = r * -1;
	return (r);
}

static int	ft_pow(int base, int exp)
{
	int	i;
	int	r;

	r = 1;
	i = 0;
	while (i < exp)
	{
		r = r * base;
		++i;
	}
	return (r);
}

int	ft_isspace(int c)  // Remove static keyword and match libft.h signature
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

static int	find_start_point(const char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		++i;
	return (i);
}
