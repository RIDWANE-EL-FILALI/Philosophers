#include "philosophers.h"

int main(int ac, char **av)
{
    t_variables *variables;
    
    if (ac - 1 == 4 || ac - 1 == 5)
    {
        if (check_valid_input(ac, av) == 1)
            printf("invalid input");
        variables = iniciate_variables(ac, av);
        // printf("number_of_philosophers %d\n", variables->number_of_philosophers);
        // printf("time_to_die %ld\n", variables->time_to_die);
        // printf("time_to_eat %ld\n", variables->time_to_eat);
        // printf("time_to_sleep %ld\n", variables->time_to_sleep);
        // printf("eat_count %d\n", variables->eat_count);
        if (begin_eating(variables) == 1)
            printf("there was an error starting the sumulation\n");
    }
    else
        printf("there is an error in parsing\n");
    return (0);
}

static int begin_eating(t_variables *variables)
{
    unsigned int i;

    variables->start_time = 
}