#include "philosophers.h"

int check_valid_input(int ac, char **av)
{
    if (check_digit(ac, av) == 1)
        return (1);
    if (check_max_int(ac, av) == 1)
        return (1);
    return (0);
}

int check_max_int(int ac, char **av)
{
    long num;
    int i = 1;

    while (av[i])
    {
        num = ft_atoi(av[i]);
        if (num > 2147483647 || num < -2147483648)
            return (1);
        i++;
    }
    return (0);
}

int check_digit(int ac, char **av)
{
    int i;
    int j;

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
