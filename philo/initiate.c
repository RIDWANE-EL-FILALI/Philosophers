/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:24:36 by rel-fila          #+#    #+#             */
/*   Updated: 2023/06/07 12:24:37 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	initiate_struct(t_var *var)
{
	var->phil = malloc(sizeof(t_phil) * var->num_phil);
	var->forks = malloc(sizeof(pthread_mutex_t) * var->num_phil);
	var->log = malloc(sizeof(pthread_mutex_t));
	var->meal = malloc(sizeof(pthread_mutex_t));
	if (initiate_mutexeses(var) == 1 || initiate_philo(var) == 1)
	{
		free(var->phil);
		free(var->forks);
		return (0);
	}
	return (1);
}

int	initiate_philo(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->num_phil)
	{
		var->phil[i].must_eat = var->must_eat_count;
		var->phil[i].times_ate = 0;
		var->phil[i].pos = i + 1;
		var->phil[i].fr_fork = i;
		var->phil[i].sc_fork = (i + 1) % var->num_phil;
		var->phil[i].var = var;
		i++;
	}
	return (0);
}

int	initiate_mutexeses(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->num_phil)
	{
		if (pthread_mutex_init(&var->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(var->meal, NULL))
		return (1);
	if (pthread_mutex_init(var->log, NULL))
		return (1);
	return (0);
}

void	fill_struct(int ac, char **av, t_var *var)
{
	var->num_phil = ft_atoi(av[1]);
	var->time_to_die = ft_atoi(av[2]);
	var->time_to_eat = ft_atoi(av[3]);
	var->time_to_sleep = ft_atoi(av[4]);
	var->must_eat_count = -1;
	if (ac - 1 == 5)
		var->must_eat_count = ft_atoi(av[5]);
	var->time_of_death = 0;
	var->index_of_the_phil_who_died = 0;
}
