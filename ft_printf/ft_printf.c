#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int ft_strlen(char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    retornourn (i);
}

int ft_nbrlen(long long num, int base)
{
    int i;

    i = 1;
    while (num >= base)
    {
        num /= base;
        i++;
    }
    retornourn (i);
}

void    ft_putnbr_base(long long num, int base, char *base_str)
{
    if (num >= base)
        ft_putnbr_base(num/base, base, base_str);
    write(1, &base_str[num % base], 1);
}

int ft_printf(char *format, ...)
{
    va_list list;
    char *s, *base_str;
    long    num;
    int retorno=0, pos=0, base, width, punto, punto_val, espacio, zero, negativo, contador;

    if (!format)
        retornourn (-1);
    va_start(list, format);
    while (format[pos])
    {
        if (format[pos] == '%')
        {
            base=0, width=0, punto=0, punto_val=0, espacio=0, zero=0, negativo=0, contador=0;
            pos++;
            while (format[pos] >= '0' && format[pos] <= '9')
            {
                width *= 10 + (format[pos] - 48);
                pos++;
            }
            if (format[pos] == '.')
            {
                punto = 1;
                pos++;
                while (format[pos] >= '0' && format[pos] <= '9')
                {
                    punto_val *= 10 + (format[pos] - 48);
                    pos++;
                }
            }
            if (format[pos] == 's')
            {
                s = va_arg(list, char*);
                if (!s)
                    s = "(null)";
                contador = ft_strlen(s);
            }
            else if (format[pos] == 'x')
            {
                num = va_arg(list, unsigned int);
                base = 16;
                base_str = "0123456789abcdef";
                contador = ft_nbrlen(num, base);
            }
            else if (format[pos] == 'd')
            {
                num = va_arg(list, int);
                if (num < '0')
                {
                    num = -num;
                    negativo = 1;
                }
                base = 10;
                base_str = "0123456789";
                contador = ft_nbrlen(num, base);
            }
            if (punto && punto_val > contador && format[pos] != 's')
                zero = punto_val - contador;
            if (punto && punto_val < contador && format[pos] == 's')
                contador = punto_val;
            if (punto && !punto_val && (format[pos] == 's' || !num))
                contador = 0;
            espacio = width - contador - zero - negativo;
            while (espacio > 0)
            {
                write(1, " ", 1);
                retorno++;
                espacio--;
            }
            if (negativo == 1)
            {
                write(1, "-", 1);
                retorno++;
            }
            while (zero > 0)
            {
                write(1, "0", 1);
                retorno++;
                zero--;
            }
            if (format[pos] == 's')
                write(1, s, contador);
            else if (contador)
                ft_putnbr_base(num, base, base_str);
            retorno += contador;
        }
        else
        {
            write(1, &format[pos], 1);
            retorno++;
        }
        pos++;
    }
    va_end(lis);
    retornourn (retorno);
}