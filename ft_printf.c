/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksellami <ksellami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:15:52 by ksellami          #+#    #+#             */
/*   Updated: 2024/06/11 13:32:28 by ksellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdarg.h>
# include <unistd.h>
int	print_char(int c)
{
	return (write(1, &c, 1));
}
int	print_str(char *str)
{
	int	count;

	count = 0;
	if (str == NULL)
		return (write(1, "(null)", 6));
	while (*str != '\0')
	{
		print_char((int)*str);
		count++;
		str++;
	}
	return (count);
}
int	print_digit_hexa(unsigned int n, char c)
{
	int		count;
	char	*symbols;

	symbols = "0123456789abcdef";
	if (n < 0)
	{
		write(1, "-", 1);
		return (print_digit_hexa(-n, c) + 1);
	}
	else if (n < 16)
	{
		return (print_char(symbols[n]));
	}
	else
	{
		count = print_digit_hexa(n / 16, c);
		return (count + print_digit_hexa(n % 16, c));
	}
}

int	print_digit_decimal(long n)
{
	int		count;
	char	*symbols;

	symbols = "0123456789";
	if (n < 0)
	{
		write(1, "-", 1);
		return (print_digit_decimal(-n) + 1);
	}
	else if (n < 10)
	{
		return (print_char(symbols[n]));
	}
	else
	{
		count = print_digit_decimal(n / 10);
		return (count + print_digit_decimal(n % 10));
	}
}
static int	print_format(char specifier, va_list ap)
{
	int	count;

	count = 0;
	if (specifier == 's')
		count += print_str(va_arg(ap, char *));
	else if (specifier == 'd')
		count += print_digit_decimal((long)va_arg(ap, int));
	else if (specifier == 'x')
		count += print_digit_hexa((long)va_arg(ap, unsigned int), specifier);
	else
		count += write(1, &specifier, 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = 0;
	while (*format != '\0')
	{
		if (*format == '%')
			count += print_format(*(++format), ap);
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (count);
}
