/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:17:39 by amtan             #+#    #+#             */
/*   Updated: 2025/12/05 18:48:38 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(int c, size_t *printed)
{
	unsigned char	ch;

	if (*printed >= (size_t)INT_MAX)
		return (-1);
	ch = (unsigned char)c;
	if (write(1, &ch, 1) < 0)
		return (-1);
	(*printed)++;
	return (1);
}
