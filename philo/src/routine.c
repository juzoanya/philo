/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 20:31:38 by juzoanya          #+#    #+#             */
/*   Updated: 2022/10/10 22:34:47 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_dead(t_philo *philo)
{
	long	time;
	long	std_eat;

	pthread_mutex_lock(&philo->env->access);
	time = gettime();
	std_eat = philo->std_eat;
	pthread_mutex_unlock(&philo->env->access);
	if ((std_eat == 0 && time - philo->env->start \
		> (philo->env->args.tt_die / 1000)) \
		|| (std_eat > 0 && time - std_eat > (philo->env->args.tt_die / 1000)))
	{
		pthread_mutex_lock(&philo->env->access);
		philo->state = died;
		pthread_mutex_unlock(&philo->env->access);
		return (1);
	}
	return (0);
}

static int	exec_task(t_philo *philo)
{
	int	right;
	int	left;

	right = 0;
	left = 0;
	if (philo->env->args.nbr < 2)
		return (0);
	left = lock_left(philo);
	right = lock_right(philo);
	if (right && left)
		ft_eating(philo);
	else if (!right && left)
		pthread_mutex_unlock(&philo->env->forks[philo->fork.left]);
	else if (right && !left)
		pthread_mutex_unlock(&philo->env->forks[philo->fork.right]);
	return (1);
}

static void	*checker_task(t_philo *philo, t_env *env, int i)
{
	pthread_mutex_lock(&env->print);
	printf("%s%ld %d died\e[0m\n", "\e[1;31m", \
		gettime() - env->start, philo[i].id);
	pthread_mutex_unlock(&env->print);
	pthread_mutex_lock(&env->death);
	env->dead = 1;
	pthread_mutex_unlock(&env->death);
	i = -1;
	while (++i < env->args.nbr)
	{
		pthread_mutex_lock(&env->death);
		philo[i].env->dead = 1;
		pthread_mutex_unlock(&env->death);
	}
	return (NULL);
}

void	*checker(void *content)
{
	t_philo	*philo;
	t_env	*env;
	int		i;
	int		eat_cnt;

	philo = (t_philo *)content;
	env = philo[0].env;
	eat_cnt = eat_count_set(philo, 0);
	i = 0;
	while (1)
	{
		if (i == env->args.nbr)
			i = 0;
		if ((philo->env->args.nbr_meal > 0 \
			&& eat_cnt == philo->env->args.nbr_meal) || env->dead == 1)
			break ;
		else if (philo_dead(&philo[i]))
			return (checker_task(philo, env, i));
		i++;
		if (i < env->args.nbr)
			eat_cnt = eat_count_set(philo, i);
	}
	return (NULL);
}

void	*routine(void *content)
{
	t_philo	*philo;
	int		d_status;
	int		eat_cnt;

	philo = (t_philo *)content;
	if (philo->id % 2 == 0)
		usleep(philo->env->args.tt_eat / 2);
	d_status = death_lock_assign(philo);
	eat_cnt = eat_count_set(philo, 0);
	while (1)
	{
		if ((philo->env->args.nbr_meal > 0 \
			&& eat_cnt == philo->env->args.nbr_meal) || d_status == 1)
			break ;
		else
		{
			exec_task(philo);
			d_status = death_lock_assign(philo);
			pthread_mutex_lock(&philo->env->access);
			eat_cnt = philo->eat_cnt;
			pthread_mutex_unlock(&philo->env->access);
		}
	}
	return (NULL);
}
