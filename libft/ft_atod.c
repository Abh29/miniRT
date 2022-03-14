#include "libft.h"

int		ft_check_dbl(const char *str)
{
	int dot;

	if (str == NULL)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	dot = 0;
	while (*str)
	{
		if (*str == '.')
		{
			if (dot == 0)
				dot = 1;
			else
				return (0);
		}
		if (ft_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

int		ft_pow_ten(int i)
{
	int out;

	out = 1;
	if (i < 0)
		i *= -1;
	while (out <= i)
		out *= 10;
	return (out);
}

double	ft_atod(const char *str)
{
	char	*p;
	int		first;
	int		second;
	int		pow;

	if (ft_check_dbl(str) == 0)
		return (0);
	p = ft_strchr(str, '.');
	if (p == NULL)
		second = 0;
	else
	{
		*p = 0;
		second = ft_atoi(p + 1);
	}
	first = ft_atoi(str);
	pow = ft_pow_ten(first);
	first = first * pow + second;
	return ((float)(first * 1.0) / pow);
}
