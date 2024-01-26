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

void put_digit(long number, int base, int *len)
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

void	ft_puthex(unsigned int n, int *len)
{
	char	s[8];
	char	*base;
	int		i;

	base = "0123456789abcdef";
	i = 0;
	if (n == 0)
	{
		*len += write(1, "0", 1);
		//ft_putchar('0', len);
		return ;
	}
	while (n != 0)
	{
		s[i] = base [n % 16];
		n = n / 16;
		i++;
	}
	while (i--)
		*len += write(1, &s[i], 1);
		//ft_putchar(s[i], len);
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
				ft_puthex(va_arg(args, int), &ret_len);
				//put_digit(va_arg(args, int),16, &ret_len);
		}
		else 
			ret_len += write(1, string, 1);
		string += 1;
	}
	return(va_end(args), ret_len);
}

int main()
{
	int i = 2125454457;
	char *s = "vdfgdfgdfgdsvfghqq";
	int x = 1545311245;

	ft_printf(" number: %x\n", -1);
	printf(" number: %x\n ", -1);
}