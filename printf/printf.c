#include <unistd.h>

void put_string(char *str, int *len)
{
	if (!str)
		str = "(null)";
	while(*str)
		*len += write(1, str++, 1);
}

void put_digit(long long int number, int base, int *len)
{
	char *cipher = "0123456789abcdef";
	if(number < 0)
	{
		number *= -1;
		*len += write(1,"-",1);
	}
	if (number >= base)
		put_digit(number/base, base, len);
	*len += write(1, &cipher[number], 1);
}

int ft_printf(const char *format, ... )
{
	
}