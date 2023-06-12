/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:24:57 by rel-fila          #+#    #+#             */
/*   Updated: 2023/06/08 15:15:29 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *) str1;
	s2 = (unsigned char *) str2;
	while (n > 0)
	{
		if (*s1 > *s2 || *s1 < *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

void	ft_free(t_var *var)
{
	free(var->phil);
	free(var->forks);
	free(var->log);
	free(var->meal);
}

void	ft_just_unlock(t_phil *phil)
{
	pthread_mutex_unlock(phil->var->meal);
	pthread_mutex_unlock(&phil->var->forks[phil->sc_fork]);
	pthread_mutex_unlock(&phil->var->forks[phil->fr_fork]);
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
