#include <stdio.h>
#include "ft_printf.h"
#include <limits.h>

int	main(void)
{
	char c = '%';
	char *str = "Hello World 42 Singapore";
	char *empty_str = "";
	char *null_str = NULL;
	int	int_max = INT_MAX;
	int int_min = INT_MIN;
	int zero = 0;
	unsigned int uint_max = UINT_MAX;
	void *ptr = &c;
	void *null_ptr = NULL;

	printf("==printf==\nchar -> %c\nstr  -> %s\nempty_str -> %s\nnull_str -> %s\nint_max -> %i\nint_min -> %d\nzero -> %u\nuint_max -> %u\nptr -> %p\nnull_ptr -> %p\npercent sign -> %%\nno percent sign -> %",
			                	c,		str,			empty_str,			null_str,		int_max,	int_min,	zero,		uint_max,		ptr,			null_ptr);
	printf("\n");
	ft_printf("==ft_printf==!\nchar -> %c\nstr  -> %s\nempty_str -> %s\nnull_str -> %s\nint_max -> %i\nint_min -> %d\nzero -> %u\nuint_max -> %u\nptr -> %p\nnull_ptr -> %p\npercent sign -> %%\nno percent sign -> %",
			                	c,		str,			empty_str,			null_str,		int_max,	int_min,	zero,		uint_max,		ptr,			null_ptr);
}
