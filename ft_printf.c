/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:41:17 by amtan             #+#    #+#             */
/*   Updated: 2025/11/27 18:48:11 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			count += handle_conversion(&format, &ap);
			format++;
		}
		else
		{
			ft_putchar_rd(*format, 1);
			count++;
			format++;
		}
		format++;
	}
	va_end(ap);
	return (count);
}

