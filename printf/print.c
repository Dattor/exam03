#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

void put_str(char *s, int *len)
{
	if(!s)
		s = "(null)";
	while (s)
		*len += write(1, s++, 1);
}

void put_nbr(long nbr, int base, int *len)
{
	char *ciph = "0123456789abcdef";
	if(nbr < 0)
	{
		*len += write(1, '-', 1);
		nbr *= -1;
	}
	if(nbr >= base)
		put_nbr(nbr/base, base, len);
	write(1, &ciph[nbr%base],1);
}


int ft_printf(const char *s, ...)
{
	int len = 0;
	va_list args;
	va_start(args, s);

	while(*s)
	{
		if(*s == '%' && (*(s + 1) == 's' || *(s + 1) == 'd' || *(s+1) == 'x'  ))
		{
			s += 1;
			if (*s == 's')
				put_str(va_arg(args, char *), &len);
			else if (*s == 'd')
				put_nbr(va_arg(args, int), 10, &len);
			else if (*s == 'x' )
				put_nbr(va_arg(args, int), 16, &len);
		}
		else
			len += write(1, s, 1);
		s++;
	}

	return(va_end(args), len);
}