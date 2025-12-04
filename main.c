#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>

int	main(void)
{
	int	unknown;

	// int		a;
	// int		b;
	// char	*s;
	// s = NULL;
	// a = printf("stdio: %s[%%]\n", s);
	// b = ft_printf("mine : %s[%%]\n", s);
	// printf("ret stdio = %d, ret mine = %d\n", a, b);
	unknown = printf("what will this print --> %w interesting....", 42);
	printf("%d\n", unknown);
}
