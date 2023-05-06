#include "philosophers.h"

int main(int ac, char **av)
{
    t_variables *variables;
    
    if (ac - 1 == 4 || ac - 1 == 5)
    {
        if (check_valid_input(ac, av) == 1)
            printf("invalid input");
        variables = iniciate_variables(ac, av);
        if (begin_eating(variables) == 1)
            printf("there was an error starting the sumulation\n");
    }
    else
        printf("there is an error in parsing\n");
    return (0);
}

static bool begin_eating(t_variables *variables)
{
    unsigned int i;

    variables->start_time = get_time_in_ms();
    i = 0;
    while (i < variables->nb_philos)
    {
        if (pthread_create(&variables->philos[i]->thread, NULL, &philosopher, variables->philos[i]) != 0)
            exit(1);
        i++;
    }
    if (variables->nb_philos > 1)
    {
        if (pthread_create(&variables->grim_reaper, NULL, &grim_reaper, variables) != 0)
            exit(1);
    }
    return (0);
}

time_t  get_time_in_ms(void)
{
    time_t time;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (time);
}

void *philosopher(void *data)
{
    t_philo *philo;
    philo = (t_philo *)data;
    if (philo->table->must_eat_count == 0)
        return (NULL);
    pthread_mutex_lock(&philo->meal_time_lock);
    philo->last_meal = philo->table->start_time;
    pthread_mutex_unlock(&philo->meal_time_lock);
    sim_start_delay(philo->table->start_time);
}

void sim_start_delay(time_t start_time)
{
    while (get_time_in_ms() < start_time)
        continue ;
}