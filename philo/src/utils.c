/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 10:28:51 by juzoanya          #+#    #+#             */
/*   Updated: 2022/10/02 13:20:55 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n')
	{
		return (1);
	}
	else if (c == '\r' || c == '\t' || c == '\v')
	{
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
		sign *= -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = ((result * 10) + (nptr[i] - '0'));
		i++;
	}
	return (sign * result);
}

long	gettime(void)
{
	struct timeval	timeval;
	long			time;

	gettimeofday(&timeval, NULL);
	time = (long)timeval.tv_sec * 1000 + (long)(timeval.tv_usec / 1000);
	return (time);
}

int	is_dead_philo(t_env *env, t_philo *philo)
{
	long int	time;
	long		std_eat;

	pthread_mutex_lock(&env->time);
	time = gettime();
	std_eat = philo->std_eat;
	pthread_mutex_unlock(&env->time);
	if (time - std_eat > (philo->args.tt_die / 1000))
	{
		pthread_mutex_lock(&env->print);
		printf("%s%ld %d died\e[0m\n", "\e[1;31m", time, philo->id);
		pthread_mutex_unlock(&env->print);
		pthread_mutex_lock(&env->death);
		env->dead = 1;
		pthread_mutex_unlock(&env->death);
		return (1);
	}
	return (0);
}
