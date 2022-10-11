/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 21:49:07 by juzoanya          #+#    #+#             */
/*   Updated: 2022/10/10 21:53:30 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(void)
{
	struct timeval	timeval;
	long			time;

	gettimeofday(&timeval, NULL);
	time = (long)timeval.tv_sec * 1000 + (long)(timeval.tv_usec / 1000);
	return (time);
}

int	state_lock_assign(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->env->access);
	state = philo->state;
	pthread_mutex_unlock(&philo->env->access);
	return (state);
}

int	death_lock_assign(t_philo *philo)
{
	int	death;

	pthread_mutex_lock(&philo->env->death);
	death = philo->env->dead;
	pthread_mutex_unlock(&philo->env->death);
	return (death);
}

int	eat_count_set(t_philo *philo, int i)
{
	int	eat_cnt;

	pthread_mutex_lock(&philo->env->access);
	eat_cnt = philo[i].eat_cnt;
	pthread_mutex_unlock(&philo->env->access);
	return (eat_cnt);
}
