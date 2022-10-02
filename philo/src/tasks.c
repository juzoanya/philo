/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:29:48 by juzoanya          #+#    #+#             */
/*   Updated: 2022/10/02 13:38:05 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_left(t_env *env, t_philo *philo)
{
	int	dead_state;
	
	pthread_mutex_lock(&env->death);
	dead_state = env->dead;
	pthread_mutex_unlock(&env->death);
	if (pthread_mutex_lock(&env->forks[philo->fork.left]) == 0)
	{
		pthread_mutex_lock(&env->print);
		if (dead_state == 0)
			printf("%s%ld %d has taken a left fork\e[0m\n", "\e[0;36m", \
				gettime(), philo->id);
		pthread_mutex_unlock(&env->print);
		return (1);
	}
	return (0);
}

int	lock_right(t_env *env, t_philo *philo)
{
	int	dead_state;
	
	pthread_mutex_lock(&env->death);
	dead_state = env->dead;
	pthread_mutex_unlock(&env->death);
	if (pthread_mutex_lock(&env->forks[philo->fork.right]) == 0)
	{
		pthread_mutex_lock(&env->print);
		if (dead_state == 0)
			printf("%s%ld %d has taken a right fork\e[0m\n", "\e[0;36m", \
				gettime(), philo->id);
		pthread_mutex_unlock(&env->print);
		return (1);
	}
	return (0);
}

void	ft_thinking(t_env *env, t_philo *philo)
{
	int	dead_state;
	
	pthread_mutex_lock(&env->death);
	dead_state = env->dead;
	pthread_mutex_unlock(&env->death);
	pthread_mutex_lock(&env->print);
	if (dead_state == 0)
		printf("%s%ld %d is thinking\e[0m\n", "\e[1;33m", gettime(), \
			philo->id);
	pthread_mutex_unlock(&env->print);
}

void	ft_eating(t_env *env, t_philo *philo)
{
	int	dead_state;
	
	pthread_mutex_lock(&env->death);
	dead_state = env->dead;
	pthread_mutex_unlock(&env->death);
	
	pthread_mutex_lock(&env->time);
	philo->std_eat = gettime();
	pthread_mutex_unlock(&env->time);
	pthread_mutex_lock(&env->print);
	if (dead_state == 0)
		printf("%s%ld %d is eating\e[0m\n", "\e[1;32m", \
			philo->std_eat, philo->id);
	pthread_mutex_unlock(&env->print);
	usleep(env->args.tt_eat);
	pthread_mutex_unlock(&env->forks[philo->fork.right]);
	pthread_mutex_unlock(&env->forks[philo->fork.left]);
	pthread_mutex_lock(&env->var_chg);
	philo->eat_cnt++;
	pthread_mutex_unlock(&env->var_chg);
	pthread_mutex_lock(&env->print);
	if (dead_state == 0)
		printf("%s%ld %d is sleeping\e[0m\n", "\e[1;35m", \
			gettime(), philo->id);
	pthread_mutex_unlock(&env->print);
	usleep(philo->args.tt_sleep);
	if (dead_state == 0)
		ft_thinking(env, philo);
}
