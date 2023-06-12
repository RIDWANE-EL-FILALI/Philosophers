/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:18:27 by rel-fila          #+#    #+#             */
/*   Updated: 2023/06/08 15:09:41 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_var	t_var;
typedef struct s_phil
{
	int			times_ate;
	int			pos;
	int			fr_fork;
	int			sc_fork;
	time_t		last_time_ate;
	pthread_t	thread;
	int			must_eat;
	t_var		*var;
}	t_phil;

typedef struct s_var
{
	time_t			time_of_death;
	int				index_of_the_phil_who_died;
	int				num_phil;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	time_t			start_time;
	int				stop_sign;
	int				max_ate;
	t_phil			*phil;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*log;
	pthread_mutex_t	*meal;
}	t_var;

long	ft_atoi(const char *str);
int		check_valid_input(int ac, char **av);
int		check_max_int(int ac, char **av);
int		check_digit(int ac, char **av);
size_t	ft_strlen(const char *s);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
void	fill_struct(int ac, char **av, t_var *var);
int		initiate_struct(t_var *var);
int		initiate_philo(t_var *var);
int		initiate_mutexeses(t_var *var);
void	fill_struct(int ac, char **av, t_var *var);
time_t	get_time_in_ms(void);
void	*application(void *data);
int		start_simulation(t_var *var);
void	ft_odd_phil(t_phil *phil);
void	ft_lone_ranger(t_phil *phil);
int		ft_sleep(t_phil *phil, long time);
void	ft_free(t_var *var);
void	ft_just_unlock(t_phil *phil);

#endif