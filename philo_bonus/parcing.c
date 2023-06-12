/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 02:17:36 by rel-fila          #+#    #+#             */
/*   Updated: 2023/06/12 02:17:36 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

long	ft_atoi(const char *str)
{
	int		i;
	long	rest;
	int		sign;

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

int	check_valid_input(int ac, char **av)
{
	int	i;
	int	check;

	i = 1;
	if (check_digit(ac, av) == 1)
		return (printf("Error other then digits\n"), 1);
	if (check_max_int(ac, av) == 1)
		return (printf("Error max int\n"), 1);
	while (i < ac)
	{
		check = ft_atoi(av[i]);
		if (i == 1 && (check <= 0 || check > 200))
			return (printf("Error more then the allowed phil\n"), 1);
		if ((i > 1 && i < 5) && (check < 60))
			return (printf("error you've entered a time < 60\n"), 1);
		i++;
	}
	return (0);
}

int	check_max_int(int ac, char **av)
{
	long	num;
	int		i;

	i = 1;
	(void)ac;
	while (av[i])
	{
		num = ft_atoi(av[i]);
		if (num > 2147483647 || num < -2147483648)
			return (1);
		i++;
	}
	return (0);
}

int	check_digit(int ac, char **av)
{
	int	i;
	int	j;

	(void)ac;
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
