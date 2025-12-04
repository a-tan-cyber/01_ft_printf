/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:30:21 by amtan             #+#    #+#             */
/*   Updated: 2025/12/04 17:27:01 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_pointer(void *p, char specifier, size_t *printed)
{
	int	tmp;
	int	ret;

	if (!p)
		return (print_str("(nil)", printed));
	tmp = print_str("0x", printed);
	if (tmp < 0)
		return (-1);
	ret = print_unsigned_base((unsigned long)p, specifier, printed);
	if (ret < 0)
		return (-1);
	return (ret + tmp);
}
