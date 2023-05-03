# ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_variabl
{
    unsigned int number_of_philosophers;
    time_t time_to_die;
    time_t time_to_eat;
    time_t time_to_sleep;
    int eat_count;
    time_t start_time;
}   t_variables;






long    ft_atoi(const char *str);
t_variables *iniciate_variables(int ac, char **av);
int check_valid_input(int ac, char **av);
int check_max_int(int ac, char **av);
int check_digit(int ac, char **av);





#endif
