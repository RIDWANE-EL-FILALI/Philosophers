#include "philosophers.h"

t_variables *iniciate_variables(int ac, char **av)
{
    t_variables *variables;

    variables = malloc(sizeof(t_variables) * 1);
    if (!variables)
        exit(1);
    variables->number_of_philosophers = ft_atoi(av[1]);
    variables->time_to_die = ft_atoi(av[2]);
    variables->time_to_eat = ft_atoi(av[3]);
    variables->time_to_sleep = ft_atoi(av[4]);
    if (av[5])
        variables->eat_count = ft_atoi(av[5]);
    else
        variables->eat_count = -1;
    return (variables);
}
