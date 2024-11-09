/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <jganivet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:07:06 by jganivet          #+#    #+#             */
/*   Updated: 2021/12/13 12:22:21 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>

int				ft_printf(const char *fmt, ...);
int				flag_value(char *s, char f);
int				format_print_char(int i, char *p);
int				format_print_str(char *s, char *p);
int				format_print_int(int i, char *p);
int				format_print_uint(unsigned int i, char *p);
int				format_print_ptr(void *ptr, char *p);
int				format_print_hex(unsigned int i, char *p);
int				format_print_percent(char *p);
int				is_in_str(char *s, char c);
int				pad(char c, int n);
long int		val_abs(long int i);
unsigned long	puiss(int base, int n);
int				pad(char c, int n);
size_t			ft_strlen(const char *s);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);

#endif
