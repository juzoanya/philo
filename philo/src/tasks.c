/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:29:48 by juzoanya          #+#    #+#             */
/*   Updated: 2022/10/10 22:14:50 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_left(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->env->forks[philo->fork.left]) != 0)
		return (0);
	pthread_mutex_lock(&philo->env->print);
	pthread_mutex_lock(&philo->env->death);
	if (philo->env->dead != 1)
		printf("%s%ld %d has taken a left fork\e[0m\n", "\e[0;36m", \
			gettime() - philo->env->start, philo->id);
	pthread_mutex_unlock(&philo->env->death);
	pthread_mutex_unlock(&philo->env->print);
	return (1);
}

int	lock_right(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->env->forks[philo->fork.right]) != 0)
		return (0);
	pthread_mutex_lock(&philo->env->print);
	pthread_mutex_lock(&philo->env->death);
	if (philo->env->dead != 1)
		printf("%s%ld %d has taken a right fork\e[0m\n", "\e[0;36m", \
			gettime() - philo->env->start, philo->id);
	pthread_mutex_unlock(&philo->env->death);
	pthread_mutex_unlock(&philo->env->print);
	return (1);
}

void	ft_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->print);
	pthread_mutex_lock(&philo->env->death);
	if (philo->env->dead != 1)
		printf("%s%ld %d is thinking\e[0m\n", "\e[1;33m", \
			gettime() - philo->env->start, philo->id);
	pthread_mutex_unlock(&philo->env->death);
	pthread_mutex_unlock(&philo->env->print);
}

void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->access);
	philo->std_eat = gettime();
	pthread_mutex_unlock(&philo->env->access);
	pthread_mutex_lock(&philo->env->print);
	pthread_mutex_lock(&philo->env->death);
	if (philo->env->dead != 1)
		printf("%s%ld %d is eating\e[0m\n", "\e[1;32m", \
			philo->std_eat - philo->env->start, philo->id);
	pthread_mutex_unlock(&philo->env->death);
	pthread_mutex_unlock(&philo->env->print);
	usleep(philo->env->args.tt_eat);
	pthread_mutex_lock(&philo->env->access);
	philo->eat_cnt++;
	pthread_mutex_unlock(&philo->env->access);
	pthread_mutex_unlock(&philo->env->forks[philo->fork.right]);
	pthread_mutex_unlock(&philo->env->forks[philo->fork.left]);
	pthread_mutex_lock(&philo->env->print);
	pthread_mutex_lock(&philo->env->death);
	if (philo->env->dead != 1)
		printf("%s%ld %d is sleeping\e[0m\n", "\e[1;35m", \
			gettime() - philo->env->start, philo->id);
	pthread_mutex_unlock(&philo->env->death);
	pthread_mutex_unlock(&philo->env->print);
	usleep(philo->env->args.tt_sleep);
	ft_thinking(philo);
}
