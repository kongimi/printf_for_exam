/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <niran.analas@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:14:21 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/15 19:43:36 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int find_len(long c, int base)
{
	int len;
	int my_base;
	long buf;

	len  = 1;
	my_base = base;
	buf = c;
	if (buf < 0)
	{
		len++;
		buf *= (-1);
	}
	while (buf >= my_base)
	{
		len++;
		buf /= my_base;
	}
	return (len);
}

char *ft_itoa(long c, int base)
{
	char *res;
	int len;
	long buf;
	int i;
	char *my_num = "0123456789abcdef";

	len = find_len(c, base);
	res = malloc(sizeof(char) * len + 1);
	buf = c;
	i = 0;
	if (buf < 0)
	{
		buf *= (-1);
	}
	while (i <= len)
	{
		res[len - i - 1] = my_num[buf % base];
		buf /= base;
		i++;
	}
	if (c < 0)
		res[0] = '-';
	res[len] = 0;
	return (res);
}

int ft_writenum(long c, int base)
{
	int len;
	int i;
	char *res;

	i = 0;
	res = ft_itoa(c, base);
	len = 0;
	while (res[i])
	{
		len += write(1, res + i, 1);
		i++;
	}
	free (res);
	return (len);
}

int ft_writestr(char *str)
{
	int len;
	int i;

	i = 0;
	len  = 0;
	while (str[i])
	{
		len += write(1, str + i, 1);
		i++;
	}
	return (len);
}

int check(va_list args, char str)
{
	int len;

	len  = 0;
	if (str == 's')
		len += ft_writestr(va_arg(args, char *));
	else if (str == 'd')
		len += ft_writenum(va_arg(args, int), 10);
		else if (str == 'x')
		len += ft_writenum(va_arg(args, unsigned int), 16);
	return (len);
}

int ft_printf(const char *str, ...)
{
	va_list args;
	int len;
	int i;

	va_start(args, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += check(args, str[i + 1]);
			i++;
		}
		else
			len += write(1, str + i, 1);
		i++;
	}
	va_end(args);
	return (len);
}

int main(void)
{
	char *str = "abc";
	int len;
	int a;
	int b;

	len = ft_printf("test\n");
	printf("len = %d\n", len);
	len = ft_printf("%s\n", str);
	printf("len = %d\n", len);
	a = 2345;
	len = ft_printf("%d\n", a);
	printf("len = %d\n", len);
	b = -12345;
	len = ft_printf("%d\n", b);
	printf("len = %d\n", len);
	a = 255;
	len = ft_printf("%x\n", a);
	printf("len = %d\n", len);
	a = -16;
	len = ft_printf("%x\n", a);
	printf("len = %d\n", len);
	a = INT_MAX;
	ft_printf("INT_MAX = %x\n", a);
	printf("INT_MAX original = %x\n", a);
	ft_printf("INT_MAX = %d\n", a);
	printf("INT_MAX original = %d\n", a);
	a = INT_MIN;
	ft_printf("INT_MIN = %x\n", a);
	printf("INT_MIN original = %x\n", a);
	ft_printf("INT_MIN = %d\n", a);
	printf("INT_MIN original = %d\n", a);

}