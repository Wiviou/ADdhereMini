/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <marvin42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:51:43 by jruhlman          #+#    #+#             */
/*   Updated: 2023/11/14 17:34:18 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_forme(const char **format, va_list *args)
{
	int	count;

	count = 0;
	while (**format)
	{
		if (**format == 'c')
			count += ft_printchar(va_arg(*args, int));
		else if (**format == 's')
			count += ft_printstr(va_arg(*args, char *));
		else if (**format == 'd' || **format == 'i')
			count += ft_printnum(va_arg(*args, int));
		else if (**format == 'p')
			count += ft_printptr(va_arg(*args, void *));
		else if (**format == 'u')
			count += ft_printunum(va_arg(*args, unsigned int));
		else if (**format == 'x')
			count += ft_printbnum(va_arg(*args, unsigned int), 0);
		else if (**format == 'X')
			count += ft_printbnum(va_arg(*args, unsigned int), 1);
		else
			break ;
		(*format)++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '%')
			{
				count += ft_printchar('%');
				format++;
			}
			else
				count += print_forme(&format, &args);
		}
		else
			count += write(1, format++, 1);
	}
	va_end(args);
	return (count);
}
