#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int ft_strlen(char *s)
{
    int i;
    i = 0;
    while (*s++)
        i++;
    return(i);
}

int ft_nbrlen (long long num, int base)
{
    int i;

    i = 1;
    while (num > base)
    {
        num /= base;
        i++;
    }
    return (i);
}

void ft_putnbr(long long num, int base, char *base_str)
{
    if (num >= base)
        ft_putnbr(num/base,base,base_str);
    write(1, &base_str[num % base]);
}

int ft_printf(char *format, ...)
{
    va_list list;
    long num;
    char *s, *base_str;
    int retorno = 0, posicion = 0, width, punto, punto_val, espacio, negativo, contador, base, zero;

    if (!format)
        return (-1);
    va_start(list, format);
    while (format[pos])
    {
        if (format[pos] == '%')
        {

        }
        else
        {
            write(1, &format[pos], 1);
            retorno++;
        }
        
        pos++;
    }
    va_end(list);
    return(retorno);
}

int main(void)
{
    int len;

    char *str="longitud de cadena";
    len = ft_printf("prueba");
    printf("\n %d \n", len);
}