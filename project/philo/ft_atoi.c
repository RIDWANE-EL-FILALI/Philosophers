#include "philosophers.h"

long	ft_atoi(const char *str)
{
	int	i;
	long	rest;
	int	sign;

	i = 0;
	rest = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			rest = rest * 10 + str[i] - '0';
		else
			break ;
		i++;
	}
	return (sign * rest);
}
