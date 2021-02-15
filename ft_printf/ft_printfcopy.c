#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#ifndef REAL
# define F	r += ft_printf
#else
# define F	r += printf
#endif

size_t ft_strlen(char *s)
{
	size_t len;
	len = 0;
	while (s[len])
		len++;
	return (len);
}

int nbrlen(long long num, int base)
{
	int i;

	i = 1;
	while (num >= base || num <= -base)
	{
		num = num / base;
		i++;
	}
	return (i);
}

void putnbr(long long num, int base, char *base_str)
{
	if (num >= base)
		putnbr(num/base, base, base_str);
	write(1, &base_str[num%base],1);
}

int	ft_printf(char *format, ...)
{
	va_list list;
	long num;
	char *str, *base_string;
	int ret=0,pos=0,width=0,punto=0,zero=0,esp=0,base=0,cont=0,punto_range=0,negativo=0;

	va_start(list, format);
	while(format[pos])
	{
		if (format[pos] == '%')
		{
			pos++;
			width=0,punto=0,zero=0,esp=0,base=0,cont=0,punto_range=0,negativo=0;
			while(format[pos] >= '0' && format[pos] <= '9')
			{
				width = width * 10 + (format[pos] - 48);
				pos++;
			}
			if (format[pos] == '.')
			{
				punto = 1;
				pos++;
				while(format[pos] >= '0' && format[pos] <= '9')
				{
					punto_range = punto_range * 10 + (format[pos] - 48);
					pos++;
				}
			}
			if (format[pos] == 's')
			{
				str = va_arg(list, char*);
				if (!str)
					str = "(null)";
				cont = ft_strlen(str);
			}
			if (format[pos] == 'x')
			{
				num = va_arg(list, unsigned int);
				base = 16;
				base_string = "0123456789abcdef";
				cont = nbrlen(num,base);
			}
			if (format[pos] == 'd')
			{
				num = va_arg(list, int);
				base = 10;
				base_string = "0123456789";
				cont = nbrlen(num,base);
				if (num < 0)
				{
					negativo = 1;
					num = -num;
				}
			}
			if (punto && punto_range > cont && format[pos] != 's')
				zero = punto_range - cont;
			if (punto && punto_range < cont && format[pos] == 's')
				cont = punto_range;
			if (punto && !punto_range && (format[pos] == 's' || !num))
				cont = 0;
			esp = width - zero - cont - negativo;
			while (esp-- > 0)
			{
				write(1, " ", 1);
				ret++;
			}
			if (negativo)
			{
				write(1, "-", 1);
				ret++;
			}
			while (zero-- > 0)
			{
				write(1, "0", 1);
				ret++;
			}
			if (format[pos] == 's')
				write(1, str, cont);
			else if (cont)
				putnbr(num, base,base_string);
			ret += cont;
			pos++;
		}
		else
		{
			write(1, &format[pos], 1);
			ret++;
			pos++;
		}
	}
	va_end(list);
	return(ret);
}