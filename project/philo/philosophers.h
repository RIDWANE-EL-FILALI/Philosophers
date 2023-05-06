# ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>


typedef struct s_table
{
	time_t			start_time;
	unsigned int	nb_philos;
	pthread_t		grim_reaper;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat_count;
	bool			sim_stop;
	pthread_mutex_t	sim_stop_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
    t_philo			**philos;
}	t_variables;


typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		times_ate;
	unsigned int		fork[2];
	pthread_mutex_t		meal_time_lock;
	time_t				last_meal;
	t_variables				*table;
}	t_philo;

int check_valid_input(int ac, char **av);
int check_max_int(int ac, char **av);
int check_digit(int ac, char **av);
long	ft_atoi(const char *str);




#endif
