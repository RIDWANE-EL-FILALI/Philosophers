/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 02:17:33 by rel-fila          #+#    #+#             */
/*   Updated: 2023/06/17 22:04:54 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

# define DIED 3
# define NORMAL 1
# define DONE_EATING 2

typedef struct s_phil	t_phil;

typedef struct s_var
{
	int			num_phil;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat_meals;
	time_t		start_time;
	pid_t		*pid_philos;
	t_phil		*phil;
	pthread_t	thread;
	sem_t		*write_sem;
	sem_t		*forks;
	sem_t		*eat_enough;
	sem_t		*dead_sem;
	sem_t		*exit;
}	t_var;

typedef struct s_phil {
	int			identity;
	int			all_ate;
	int			eating_routine;
	int			taking_forks;
	int			meals_counter;
	long		time_to_kill;
	long		last_eat;
	int			finish_routine;
	pthread_t	thread;
	int			nbr_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nbr_of_meals;
	pid_t		pid;
	t_var		*var;
}	t_phil;

void	initiate_var(int ac, char **av, t_var *var);
void	start_simulation(t_var *var);
void	check_kill(t_var *var, int *pid);
void	start_phil(t_phil *phil, t_var *var, pid_t *pid);
void	eat_statement(t_phil *phil);
void	*ft_eat_checker(void *data);
void	*start(void *data);
void	routine(t_phil *phil);
void	ft_sleep(int time);
void	*monitoring_pro(void *data);
void	ft_log(char *str, int identity, t_var *var, int check);
void	check_pids(pid_t *pid, t_var *var, t_phil *phil, int i);
void	initiate_sem(t_var *var);
long	ft_atoi(const char *str);
int		check_valid_input(int ac, char **av);
int		check_max_int(int ac, char **av);
int		check_digit(int ac, char **av);
time_t	get_time_in_ms(void);

#endif
