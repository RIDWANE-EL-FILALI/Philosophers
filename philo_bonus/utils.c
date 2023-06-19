/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 02:17:46 by rel-fila          #+#    #+#             */
/*   Updated: 2023/06/18 21:45:48 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	eat_statement(t_phil *phil)
{
	pthread_t	thread;

	if (phil->var->must_eat_meals)
	{
		if (pthread_create(&thread, NULL, ft_eat_checker, phil))
		{
			printf("Error creating thread\n");
			exit(1);
		}
		pthread_detach(thread);
	}
}

void	*ft_eat_checker(void *data)
{
	t_phil	*phil;
	int		i;

	i = 0;
	phil = (t_phil *)data;
	while (i < phil->var->num_phil)
	{
		sem_wait(phil->var->eat_enough);
		i++;
	}
	sem_post(phil->var->exit);
	return (NULL);
}

void	*start(void *data)
{
	t_phil		*phil;
	pthread_t	thread;

	phil = (t_phil *)data;
	if (pthread_create(&thread, NULL, &monitoring_pro, phil))
	{
		printf("Error creating thread\n");
		exit(1);
	}
	pthread_detach(thread);
	phil->meals_counter = 0;
	while (1)
		routine(phil);
	return (NULL);
}

void	routine(t_phil *phil)
{
	sem_wait(phil->var->forks);
	ft_log("has taken a fork", phil->identity, phil->var, NORMAL);
	sem_wait(phil->var->forks);
	ft_log("has taken a fork", phil->identity, phil->var, NORMAL);
	phil->meals_counter++;
	if (phil->meals_counter == phil->var->num_phil)
		sem_post(phil->var->eat_enough);
	phil->time_to_kill = get_time_in_ms() + phil->var->time_to_die;
	ft_log("is eating", phil->identity, phil->var, NORMAL);
	phil->last_eat = get_time_in_ms();
	ft_sleep(phil->var->time_to_eat);
	sem_post(phil->var->forks);
	sem_post(phil->var->forks);
	ft_log("is sleeping", phil->identity, phil->var, NORMAL);
	ft_sleep(phil->var->time_to_sleep);
	ft_log("is thinking", phil->identity, phil->var, NORMAL);
}

void	*monitoring_pro(void *data)
{
	t_phil	*phil;

	phil = (t_phil *)data;
	while (1)
	{
		if (get_time_in_ms() - phil->last_eat >= (long)phil->var->time_to_die)
		{
			sem_wait(phil->var->dead_sem);
			ft_log("died", phil->identity, phil->var, DIED);
			sem_post(phil->var->exit);
			break ;
		}
	}
	return (NULL);
}
