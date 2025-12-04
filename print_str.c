/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:47:00 by amtan             #+#    #+#             */
/*   Updated: 2025/11/29 00:02:12 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_str(char *str, size_t *printed)
{
	int	ret;

	if (!str)
		str = "(null)";
	ret = 0;
	while (*str != '\0')
	{
		ret = print_char((int)*str, printed);
		if (ret < 0)
			return (-1);
		str++;
	}
	return (ret);
}
