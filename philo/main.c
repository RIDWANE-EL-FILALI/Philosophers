#include "main.h"

int	main(int ac, char **av)
{
	t_var	var;

	if (ac - 1 == 4 || ac - 1 == 5)
	{
		if (check_valid_input(ac, av))
			return (1);
		fill_struct(ac, av, &var);
		initiate_struct(&var);
		start_simulation(&var);
	}
	else
		printf("Usage: ./philo <# philosophers> <time to die> <time to eat>\
				<time to sleep> [# times each philosopher must eat]\n");
	return (0);
}

int	start_simulation(t_var *var)
{
	int	i;

	i = 0;
	var->start_time = get_time_in_ms();
	while (i < var->num_phil)
	{
		var->phil[i].last_time_ate = get_time_in_ms();
		if (pthread_create(&var->phil[i].thread, NULL, \
					&application, &var->phil[i]))
			return (printf("Error creating threads\n"), 1);
		i++;
	}
	i = 0;
	while (i < var->num_phil)
	{
		pthread_join(var->phil[i].thread, NULL);
		i++;
	}
	if (var->stop_sign == 1)
		printf("%ld %d %s\n", var->time_of_death, \
				var->index_of_the_phil_who_died, "died");
	free(var->phil);
	free(var->forks);
	free(var->log);
	free(var->meal);
	return (0);
}

void	*application(void *data)
{
	t_phil	*phil;

	phil = (t_phil *)data;
	if (phil->var->num_phil == 1)
	{
		ft_lone_ranger(phil);
		return (NULL);
	}
	if (phil->pos % 2 == 0)
		usleep(150);
	while (phil->must_eat)
	{
		pthread_mutex_lock(&phil->var->forks[phil->fr_fork]);
		printf("%ld %d %s\n", get_time_in_ms() - phil->var->start_time, \
				phil->pos, "has taken a fork");
		pthread_mutex_lock(&phil->var->forks[phil->sc_fork]);
		printf("%ld %d %s\n", get_time_in_ms() - phil->var->start_time, \
				phil->pos, "has taken a fork");
		printf("%ld %d %s\n", get_time_in_ms() - phil->var->start_time, \
				phil->pos, "is eating");
		if (ft_sleep(phil, phil->var->time_to_eat))
			break ;
		phil->last_time_ate = get_time_in_ms();
		pthread_mutex_unlock(&phil->var->forks[phil->sc_fork]);
		pthread_mutex_unlock(&phil->var->forks[phil->fr_fork]);
		printf("%ld %d %s\n", get_time_in_ms() - phil->var->start_time, \
				phil->pos, "is sleeping");
		if (ft_sleep(phil, phil->var->time_to_sleep))
			break ;
		printf("%ld %d %s\n", get_time_in_ms() - phil->var->start_time, \
				phil->pos, "is thinking");
		phil->must_eat--;
	}
	return (NULL);
}

int	ft_sleep(t_phil *phil, long time)
{
	long	now;

	now = get_time_in_ms();
	while (get_time_in_ms() - now < time)
	{
		pthread_mutex_lock(phil->var->meal);
		if (get_time_in_ms() - phil->last_time_ate >= phil->var->time_to_die \
				&& !phil->var->stop_sign)
		{
			phil->var->stop_sign = 1;
			phil->var->index_of_the_phil_who_died = phil->pos;
			phil->var->time_of_death = get_time_in_ms() - phil->var->start_time;
			pthread_mutex_unlock(phil->var->meal);
			pthread_mutex_unlock(&phil->var->forks[phil->sc_fork]);
			pthread_mutex_unlock(&phil->var->forks[phil->fr_fork]);
			return (1);
		}
		pthread_mutex_unlock(phil->var->meal);
		pthread_mutex_lock(phil->var->meal);
		if (phil->var->stop_sign)
		{
			pthread_mutex_unlock(phil->var->meal);
			pthread_mutex_unlock(&phil->var->forks[phil->sc_fork]);
			pthread_mutex_unlock(&phil->var->forks[phil->fr_fork]);
			return (1);
		}
		pthread_mutex_unlock(phil->var->meal);
		usleep(100);
	}
	return (0);
}

void	ft_lone_ranger(t_phil *phil)
{
	pthread_mutex_lock(&phil->var->forks[phil->fr_fork]);
	printf("%ld %d %s\n", get_time_in_ms() - phil->var->start_time, \
			phil->pos, "has taken a fork");
	while (1)
	{
		if (get_time_in_ms() - phil->last_time_ate > phil->var->time_to_die)
		{
			phil->var->index_of_the_phil_who_died = phil->pos;
			phil->var->time_of_death = get_time_in_ms() - phil->var->start_time;
			phil->var->stop_sign = 1;
			break ;
		}
	}
}
