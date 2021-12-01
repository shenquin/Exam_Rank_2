/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shenquin <shenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:37:00 by shenquin          #+#    #+#             */
/*   Updated: 2021/12/01 15:37:04 by shenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

size_t ft_strlen(char *s)
{
	size_t	i = 0;

	while (s[i] != '\0')
		i++;
	return (i);
}

int		ft_intlen(long long num, int base_len)
{
	int	i = 1;
	while (num >= base_len || num <= -base_len)
	{
		num /= base_len;
		i++;
	}
	return (i);
}

void	ft_printnum(long long num, int base_len, char *base)
{
	if (num >= base_len)
		ft_printnum(num / base_len, base_len, base);
	write(1, &base[num % base_len], 1);
}

int		ft_printf(const char *format, ...)
{
	va_list list;
	char *s, *base, *str;
	int neg = 0, base_len = 0, len_str = 0, len = 0;
	long int num = 0;
	str = (char *)format;
	va_start(list, format);
	while (*str != '\0')
	{
		if (*str == '%')
		{
			neg = 0, num = 0, base_len = 0, len = 0;
			str++;
			if (*str == 's')
			{
				s = va_arg(list, char *);
				if (!s)
					s = "(null)";
				len = ft_strlen(s);
			}
			else if (*str == 'd')
			{
				num = va_arg(list, int);
				if (num < 0)
				{
					num *= -1;
					neg = 1;
				}
				base_len = 10;
				base = "0123456789";
				len = ft_intlen(num, base_len);
			}
			else if (*str == 'x')
			{
				num = va_arg(list, unsigned);
				base_len = 16;
				base = "0123456789abcdef";
				len = ft_intlen(num, base_len);
			}
			if (neg == 1)
				len_str += write(1, "-", 1);
			if (*str == 's')
				len_str += write(1, s, len);
			else if (num >= 0)
			{
				len_str += len;
				ft_printnum(num, base_len, base);
			}
		}
		else
			len_str += write(1, str, 1);
		str++;
	}
	va_end(list);
	return (len_str);
}

int main(void)
{
	printf("----> Mine\n");
	printf("\n%d\n", ft_printf("holala %d %s %x bonjour", -12, "42\0", 1248948));
	printf("\n----> Original\n");
	printf("\n%d\n", printf("holala %d %s %x bonjour", -12, "42\0", 1248948));
	return(0);
}