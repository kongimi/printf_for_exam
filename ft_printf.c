/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:55:09 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/07 15:27:51 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

int	ft_write(int c)
{
	write (1, &c, 1);
	return (1);
}

int	ft_check(va_list *args, const char *str)
{
	int	len;

	len = 0;
	if (*str == 'c')
		len += ft_write(va_arg(*args, int));
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;
	int		i;

	len = 0;
	i = 0;
	va_start(args, str);
	while (str[len])
	{
		if (str[len] == '%')
			len += ft_check(&args, str + i + 1);
		else
			len += write (1, &str[len], 1);
		printf("len = %d", len);
	}
	va_end(args);
	return (len);
}

int	main(void)
{
	char	m;

	m = '0';
	ft_printf("test = %c", m);
}
