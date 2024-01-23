#include <unistd.h>	// write
#include <stdarg.h>	// va_list
#include <stdio.h>	// printf

void put_string(char *str, int *len)
{
	if (!str)
		str = "(null)";
	while(*str)
		*len += write(1, str++, 1);
}

void put_digit(long int number, int base, int *len)
{
	char *cipher = "0123456789abcdef";
	if(number < 0)
	{
		number *= -1;
		*len += write(1,"-",1);
	}
	if (number >= base)
		put_digit(number/base, base, len);
	*len += write(1, &cipher[number%base], 1);
}

int ft_printf(const char *string, ... )
{
	int ret_len = 0;
	va_list pointer;
	va_start (pointer, string);

	while (*string)
	{
		if((*string == '%') && (*(string + 1) == 's' || *(string + 1) == 'd' || *(string + 1) == 'x'))
		{
			string += 1;
			if(*string == 's')
				put_string(va_arg(pointer, char *), &ret_len);		//After calling va_arg, the pointer is incremented to point to the next argument in the va_list. 
			else if (*string == 'd')
				put_digit(va_arg(pointer, int), 10, &ret_len);
			else if(*string == 'x')
				put_digit(va_arg(pointer, int),16, &ret_len);
		}
		else 
			ret_len += write(1, string, 1);
		string += 1;
	}
	return(va_end(pointer), ret_len);
}

int main()
{
	int i = 2125454457;
	char *s = "vdfgdfgdfgdsvfghqq";
	int x = 1545311245;

	ft_printf(" number: %d\n string: %s\n hexa: %x\n\n", i, s, x);
	printf(" number: %d\n string: %s\n hexa: %x\n", i, s, x);
}