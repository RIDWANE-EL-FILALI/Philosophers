/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 02:17:24 by rel-fila          #+#    #+#             */
/*   Updated: 2023/06/12 02:17:24 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	initiate_var(int ac, char **av, t_var *var)
{
	var->num_phil = ft_atoi(av[1]);
	var->time_to_die = ft_atoi(av[2]);
	var->time_to_eat = ft_atoi(av[3]);
	var->time_to_sleep = ft_atoi(av[4]);
	var->must_eat_meals = 0;
	if (ac - 1 == 5)
		var->must_eat_meals = ft_atoi(av[5]);
}

void	ft_log(char *str, int identity, t_var *var, int check)
{
	long	time;

	time = get_time_in_ms() - var->start_time;
	sem_wait(var->write_sem);
	if (check == DIED)
		printf("%ld %d %s\n", time, identity, str);
	else if (check == DONE_EATING)
		printf("%ld %d %s\n", time, identity, str);
	else
	{
		printf("%ld %d %s\n", time, identity, str);
		sem_post(var->write_sem);
	}
	return ;
}

void	check_pids(pid_t *pid, t_var *var, t_phil *phil, int i)
{
	if (pid[i] == -1)
	{
		while (--i >= 0)
			kill(var->pid_philos[i], SIGKILL);
		free(phil);
		free(var);
		free(pid);
		exit(1);
	}
}
