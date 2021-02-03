#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
​
size_t	ft_strlen(char *s)
{
	size_t	len;
	len = 0;
	while (s[len])
		len++;
	return (len);
}
​
int		ft_counter(long long num, int base_len)
{
	int		ct;
​
	ct = 1;
	while (num >= base_len || num <= -base_len)
	{
		num = num / base_len;
		ct++;
	}
	return (ct);
}
​
void	ft_putnum(long long num, int base_len, char *base)
{
	if (num >= base_len)
		ft_putnum(num / base_len, base_len, base);
	write(1, &base[num % base_len], 1);
}
​
int		ft_printf(char	*fromat, ...)
{
	va_list	lst;
	char	*s, *base;
	long	num;
	int		pos = 0, ct = 0, neg = 0, zero = 0, space = 0, width = 0, precision = 0, p_range = 0, ret = 0, base_len = 0;
​
	va_start(lst, fromat);
	while (fromat[pos])
	{
		if (fromat[pos] == '%')
		{
			pos++;
			ct = 0, neg = 0, zero = 0, space = 0, width = 0, precision = 0, p_range = 0;
			while (fromat[pos] >= '0' && fromat[pos] <= '9')
			{
				width = width * 10 + (fromat[pos] - 48);
				pos++;
			}
			if (fromat[pos] == '.')
			{
				pos++;
				precision = 1;
				while (fromat[pos] >= '0' && fromat[pos] <= '9')
				{
					p_range = p_range * 10 + (fromat[pos] - 48);
					pos++;
				}
			}
			if (fromat[pos] == 's')
			{
				s = va_arg(lst, char *);
				if (!s)
					s = "(null)";
				ct = ft_strlen(s);
			}
			else if (fromat[pos] == 'x')
			{
				num = va_arg(lst, unsigned int);
				base = "0123456789abcdef";
				base_len = 16;
				ct = ft_counter(num, base_len);
			}
			else if (fromat[pos] == 'd')
			{
				num = va_arg(lst, int);
				base = "0123456789";
				base_len = 10;
				ct = ft_counter(num, base_len);
				if (num < 0)
				{
					num = -num;
					neg = 1;
				}
			}
			if (precision && p_range > ct && fromat[pos] != 's')
				zero = p_range - ct;
			if (precision && p_range < ct && fromat[pos] == 's')
				ct = p_range;
			if (precision && !p_range && (fromat[pos] == 's' || !num))
				ct = 0;
			space = width - zero - ct - neg;
			while (space-- > 0)
			{
				write(1, " ", 1);
				ret++;
			}
			if (neg)
			{
				write(1, "-", 1);
				ret++;
			}
			while (zero-- > 0)
			{
				write(1, "0", 1);
				ret++;
			}
			if (fromat[pos] == 's')
				write(1, s, ct);
			else if (ct)
				ft_putnum(num, base_len, base);
			ret += ct;
			pos++;
		}
		else
		{
			write(1, &fromat[pos], 1);
			ret++;
			pos++;
		}
	}
	va_end(lst);
	return (ret);
}