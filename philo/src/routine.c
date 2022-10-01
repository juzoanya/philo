/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 20:31:38 by juzoanya          #+#    #+#             */
/*   Updated: 2022/10/01 21:19:49 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exec_actions(t_env *env, t_philo *philo)
{
	int	left;
	int	right;

	if (philo->args.nbr < 2)
		return (1);
	left = lock_left(env, philo);
	right = lock_right(env, philo);
	if (right && left)
		ft_eating(env, philo);
	else if (!right && left)
	{
		pthread_mutex_unlock(&env->forks[philo->fork.left]);
		ft_thinking(env, philo);
	}
	else if (right && !left)
	{
		pthread_mutex_unlock(&env->forks[philo->fork.right]);
		ft_thinking(env, philo);
	}
	return (1);
}

void	*routine(void *content)
{
	t_env	*env;
	t_philo	*philo;
	//int		i;

	env = (t_env *)content;
	pthread_mutex_lock(&env->var_chg);
	philo = &env->philo[env->n_th]; //i = env->n_th;
	pthread_mutex_unlock(&env->var_chg);
	if (philo->id % 2 == 0)
		usleep(philo->args.tt_eat / 2);
	if (philo->args.nbr_meal > 0)
	{
		while (philo->eat_cnt != philo->args.nbr_meal && env->dead == 0)
			exec_actions(env, philo);
	}
	else
		while (env->dead == 0)
			exec_actions(env, philo);
	return (NULL);
}

void	*checker(void *content)
{
	t_env	*env;
	t_philo	*philo;
	int		i;
	int		dead_state;
	int		eat_cnt;

	env = (t_env *)content;
	i = 0;
	philo = &env->philo[i];
	if (env->args.nbr_meal > 0)
	{
		pthread_mutex_lock(&env->death);
		dead_state = env->dead;
		pthread_mutex_unlock(&env->death);
		pthread_mutex_lock(&env->var_chg);
		eat_cnt = philo->eat_cnt;
		pthread_mutex_unlock(&env->var_chg);
		while (philo->args.nbr_meal > eat_cnt && dead_state == 0)
		{
			if (is_dead_philo(env, philo))
				break ;
			pthread_mutex_lock(&env->death);
			dead_state = env->dead;
			pthread_mutex_unlock(&env->death);
			pthread_mutex_lock(&env->var_chg);
			eat_cnt = philo->eat_cnt;
			pthread_mutex_unlock(&env->var_chg);
		}
	}
	else
	{
		pthread_mutex_lock(&env->death);
		dead_state = env->dead;
		pthread_mutex_unlock(&env->death);
		while (dead_state == 0)
		{
			if (is_dead_philo(env, philo))
				break ;
			pthread_mutex_lock(&env->death);
			dead_state = env->dead;
			pthread_mutex_unlock(&env->death);
		}
	}
	return (NULL);
}
