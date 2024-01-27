#include <unistd.h>	// write
#include <stdarg.h>	// va_list
#include <stdio.h>	// printf
#include <limits.h> //INT_MAX, MIN

void put_string(char *str, int *len)
{
	if (!str)
		str = "(null)";
	while(*str)
		*len += write(1, str++, 1);
}

void put_digit(long number, int base, int *len)
{
	char *cipher = "0123456789abcdef";
	if(number < 0 && base == 10)
	{
		number *= -1;
		*len += write(1,"-",1);
	}
	//if(base == 16)
		number = (unsigned int)number;
	if (number >= base)
		put_digit(number/base, base, len);
	*len += write(1, &cipher[number%base], 1);
}

int ft_printf(const char *string, ... )
{
	int ret_len = 0;
	va_list args;
	va_start (args, string);	//void va_start(va_list ap, last_arg); ap: a_list object that will be initialized by va_start. last_arg: The last named parameter before the ellipsis (...) in the function declaration.

	while (*string)
	{
		if((*string == '%') && (*(string + 1) == 's' || *(string + 1) == 'd' || *(string + 1) == 'x'))
		{
			string += 1;
			if(*string == 's')
				put_string(va_arg(args, char *), &ret_len);		//current argument is char *current = va_arg(args, char *), After calling va_arg, the args is incremented to point to the next argument in the va_list. 
			else if (*string == 'd')
				put_digit(va_arg(args, int), 10, &ret_len);
			else if(*string == 'x')
				put_digit(va_arg(args, int),16, &ret_len);
		}
		else 
			ret_len += write(1, string, 1);
		string += 1;
	}
	return(va_end(args), ret_len);
}

int main()
{

	ft_printf(" -1: %x  0: %x  INT_MAX: %x INT_MIN: %x \n", -1, 0, INT_MAX, INT_MIN);
	printf(" -1: %x  0: %x  INT_MAX: %x INT_MIN: %x \n", -1, 0, INT_MAX, INT_MIN);
	ft_printf(" -1: %d  0: %d  INT_MAX: %d INT_MIN: %d \n", -1, 0, INT_MAX, INT_MIN);
	printf(" -1: %d  0: %d  INT_MAX: %d INT_MIN: %d \n", -1, 0, INT_MAX, INT_MIN);

	ft_printf(" -1: %s  0: %s  INT_MAX: %s INT_MIN: %s \n", "-1", "0", "INT_MAX", "INT_MIN");
	printf(" -1: %s  0: %s  INT_MAX: %s INT_MIN: %s \n", "-1", "0", "INT_MAX", "INT_MIN");
}