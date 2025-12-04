/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_signed_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:05:04 by amtan             #+#    #+#             */
/*   Updated: 2025/12/04 17:24:10 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_signed_base(long n, char specifier, size_t *printed)
{
	int	ret;
	int	tmp;

	tmp = 0;
	if (n < 0)
	{
		tmp = print_char('-', printed);
		if (tmp < 0)
			return (-1);
		n = -n;
	}
	ret = print_unsigned_base((unsigned long)n, specifier, printed);
	if (ret < 0)
		return (-1);
	return (ret + tmp);
}
