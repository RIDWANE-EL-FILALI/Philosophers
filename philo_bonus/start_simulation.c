/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 02:17:39 by rel-fila          #+#    #+#             */
/*   Updated: 2023/06/17 22:05:50 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	start_simulation(t_var *var)
{
	pid_t	*pid;
	t_phil	*phil;

	phil = (t_phil *)malloc(sizeof(t_phil) * var->num_phil);
	pid = (pid_t *)malloc(sizeof(pid_t) * var->num_phil);
	initiate_sem(var);
	start_phil(phil, var, pid);
	sem_wait(var->exit);
	check_kill(var, pid);
	free(var);
	free(phil);
	free(pid);
}

void	initiate_sem(t_var *var)
{
	sem_unlink("/forks");
	var->forks = sem_open("/forks", O_CREAT, 0644, var->num_phil);
	sem_unlink("/write_sem");
	var->write_sem = sem_open("/write_sem", O_CREAT, 0644, 1);
	sem_unlink("/exit");
	var->exit = sem_open("/exit", O_CREAT, 0644, 0);
	sem_unlink("/dead_sem");
	var->dead_sem = sem_open("/dead_sem", O_CREAT, 0644, 1);
	sem_unlink("/eat_enough");
	var->eat_enough = sem_open("/eat_enough", O_CREAT, 0644, 0);
}

void	start_phil(t_phil *phil, t_var *var, pid_t *pid)
{
	int	i;

	i = 0;
	var->start_time = get_time_in_ms();
	while (i < var->num_phil)
	{
		pid[i] = fork();
		phil[i].last_eat = get_time_in_ms();
		phil[i].var = var;
		check_pids(pid, var, phil, i);
		if (pid[i] == 0)
		{
			phil[i].identity = i + 1;
			phil[i].pid = pid[i];
			start(&phil[i]);
		}
		i++;
	}
	eat_statement(phil);
}

void	check_kill(t_var *var, int *pid)
{
	int	i;

	i = 0;
	while (i < var->num_phil)
	{
		kill(pid[i], SIGKILL);
		i++;
	}
	sem_close(var->forks);
	sem_close(var->write_sem);
	sem_close(var->exit);
	sem_close(var->dead_sem);
}
