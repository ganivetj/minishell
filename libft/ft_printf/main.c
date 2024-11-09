/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jganivet <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:01:53 by jganivet          #+#    #+#             */
/*   Updated: 2021/12/07 16:46:05 by jganivet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>

int		ft_printf(const char *fmt, ...);
int		flag_value(char *s, char f);
int		putnbr(long int n);

int	main(void)
{
	char	*str = "abcdXXX";
	void	*ptr;
	ptr = "A";
	int wr1;
	int wr2;
	wr1 = 0;
	wr2 = 0;



	wr1 += ft_printf("%%%%%%%%%%%%%%%%%%%%\n%% PRINTF %%\n%%%%%%%%%%%%%%%%%%%%\n");

	wr2 += printf("%%%%%%%%%%%%%%%%%%%%\n%% PRINTF %%\n%%%%%%%%%%%%%%%%%%%%\n");

printf("%d/%d\n\n", wr1, wr2);

	wr1 += ft_printf("zero : '%d'\tminus 1 : %i\tint_min : %d\tint_max : '%5d'\tuint_max : %u\tChar : '%-3c'\tStr : '%5.4s'\tPointer : %p\tPercent sign : %%\n", 0, -1, INT_MIN, INT_MAX, UINT_MAX, 65, str, str);

	wr2 += printf("zero : '%d'\tminus 1 : %i\tint_min : %d\tint_max : '%5d'\tuint_max : %u\tChar : '%-3c'\tStr : '%5.4s'\tPointer : %p\tPercent sign : %%\n", 0, -1, INT_MIN, INT_MAX, UINT_MAX, 65, str, str);
	printf("%d/%d\n\n", wr1, wr2);

	wr1 = 0;
	wr2 = 0;
	ft_printf("\n\nChar formatting tests :\n");
	wr1 += ft_printf("'%-5c'\n", 'A');
	wr2 += printf("'%-5c'\n", 'A');
	wr1 += ft_printf("'%5c'\n", 'B');
	wr2 += printf("'%5c'\n", 'B');

	printf("%d/%d\n\n", wr1, wr2);	

	wr1 = 0;
	wr2 = 0;
	ft_printf("\n\nInteger formatting tests :\n");
	wr1 += ft_printf("'% d'\n", 1234);
	wr2 += printf("'% d'\n", 1234);
	ft_printf("\n");
	wr1 += ft_printf("'%d'\n", -1234);
	wr2 += printf("'%d'\n", -1234);
	ft_printf("\n");
	wr1 += ft_printf("'%+ d'\n", 1234);
	wr2 += printf("'%+d'\n", 1234);
	ft_printf("\n");
	wr1 += ft_printf("'%d'\n", -1234);
	wr2 += printf("'%d'\n", -1234);
	ft_printf("\n");

 	wr1 += ft_printf("'% -10d'\n", 1234);
 	wr2 += printf("'% -10d'\n", 1234);
 	ft_printf("\n");
	wr1 += ft_printf("'% -10d'\n", -1234);
 	wr2 += printf("'% -10d'\n", -1234);
 	ft_printf("\n");
	wr1 += ft_printf("'%-+ 10d'\n", 1234);
 	wr2 += printf("'%-+10d'\n", 1234);
 	ft_printf("\n");
	wr1 += ft_printf("'%-10d'\n", -1234);	
 	wr2 += printf("'%-10d'\n", -1234);	
	ft_printf("\n");

	wr1 += ft_printf("'%10d'\n", 1234);
	wr2 += printf("'%10d'\n", 1234);
 	ft_printf("\n");
	wr1 += ft_printf("'%10d'\n", -1234);
 	wr2 += printf("'%10d'\n", -1234);
 	ft_printf("\n");
	wr1 += ft_printf("'%+ 10d'\n", 1234);
 	wr2 += printf("'%+10d'\n", 1234);
 	ft_printf("\n");
	wr1 += ft_printf("'%10d'\n", -1234);
 	wr2 += printf("'%10d'\n", -1234);
	ft_printf("\n");

	wr1 += ft_printf("'%010d'\n", 1234);
	wr2 += printf("'%010d'\n", 1234);
 	ft_printf("\n");
	wr1 += ft_printf("'%010d'\n", -1234);
 	wr2 += printf("'%010d'\n", -1234);
 	ft_printf("\n");
	wr1 += ft_printf("'%+010d'\n", 1234);
 	wr2 += printf("'%+010d'\n", 1234);
 	ft_printf("\n");
	wr1 += ft_printf("'%010d'\n", -1234);
 	wr2 += printf("'%010d'\n", -1234);
	ft_printf("\n");
	wr1 += ft_printf("%+08d\n", -123456789);
	wr2 += printf("%+08d\n", -123456789);
	ft_printf("\n");

	wr1 += ft_printf("'%010.5d'\n", 1234);
	wr2 += printf("'%010.5d'\n", 1234);
 	ft_printf("\n");
	wr1 += ft_printf("'%010.d'\n", -1234);
 	wr2 += printf("'%010.d'\n", -1234);
 	ft_printf("\n");
	wr1 += ft_printf("'%+010.5d'\n", 1234);
 	wr2 += printf("'%+010.5d'\n", 1234);
 	ft_printf("\n");
	wr1 += ft_printf("'%-10.5d'\n", -1234);
 	wr2 += printf("'%-10.5d'\n", -1234);
	ft_printf("\n");
	wr1 += ft_printf("%+08.5d\n", -123456789);
	wr2 += printf("%+08.5d\n", -123456789);
	ft_printf("\n");

	printf("%d/%d\n\n", wr1, wr2);

	wr1 = 0;
	wr2 = 0;
	ft_printf("\n\nUnsigned int (u) formatting tests :\n");
	wr1 += ft_printf("'%20u'\n", UINT_MAX);
	wr2 += printf("'%20u'\n", UINT_MAX);
	wr1 += ft_printf("'%25.20u'\n", UINT_MAX);
	wr2 += printf("'%25.20u'\n", UINT_MAX);

	wr1 += ft_printf("'%-20u'\n", UINT_MAX);
    wr2 += printf("'%-20u'\n", UINT_MAX);
    wr1 += ft_printf("'%15.20u'\n", UINT_MAX);
    wr2 += printf("'%15.20u'\n", UINT_MAX);

	printf("%d/%d\n\n", wr1, wr2);

	wr1 = 0;
	wr2 = 0;
	ft_printf("\n\nPointer (p) formatting tests :\n");
	wr1 += ft_printf("'%-20p'\n", ptr);
	wr2 += printf("'%-20p'\n", ptr);
	wr1 += ft_printf("'%20p'\n", ptr);
	wr2 += printf("'%20p'\n", ptr);

	printf("%d/%d\n\n", wr1, wr2);
	
	wr1 = 0;
	wr2 = 0;
	ft_printf("\n\nHex (xX) formatting tests :\n");
	wr1 += ft_printf("'%X'\n", -9);
	wr2 += printf("'%X'\n", -9);
	wr1 += ft_printf("'%0#20x'\n", 1234);
	wr2 += printf("'%#020x'\n", 1234);
	wr1 += ft_printf("'%-20x'\n", 1234);
	wr2 += printf("'%-20x'\n", 1234);
	wr1 += ft_printf("'%X'\n", LONG_MAX);
	wr2 += printf("'%lX'\n", LONG_MAX);
	wr1 += ft_printf("'%X'\n", LONG_MIN);
	wr2 += printf("'%lX'\n", LONG_MIN);
	wr1 += ft_printf("'%x'\n", 9223372036854775807LL);
	wr2 += printf("'%llx'\n", 9223372036854775807LL);
	printf("%d/%d\n\n", wr1, wr2);

	return(0);
}
