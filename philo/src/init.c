/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:19:54 by juzoanya          #+#    #+#             */
/*   Updated: 2022/10/10 22:10:40 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	init_args(t_env *env, char **argv)
{
	if (!check_args(argv))
		return (err_handler(0));
	env->args.nbr = ft_atoi(argv[1]);
	env->args.tt_die = ft_atoi(argv[2]) * 1000;
	env->args.tt_eat = ft_atoi(argv[3]) * 1000;
	env->args.tt_sleep = ft_atoi(argv[4]) * 1000;
	env->dead = 0;
	env->start = gettime();
	if (argv[5])
		env->args.nbr_meal = ft_atoi(argv[5]);
	else
		env->args.nbr_meal = -1;
	return (1);
}

int	init_mutex(t_env *env)
{
	int	i;

	i = -1;
	env->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* env->args.nbr);
	if (!env->forks)
	{
		err_handler(3);
		return (0);
	}
	while (++i < env->args.nbr)
		if (pthread_mutex_init(&env->forks[i], NULL) != 0)
			return (0);
	if (pthread_mutex_init(&env->print, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&env->death, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&env->access, NULL) != 0)
		return (0);
	return (1);
}

t_philo	*init_philo(t_env *env)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo) * env->args.nbr);
	if (!philo)
	{
		err_handler (3);
		return (NULL);
	}
	while (++i < env->args.nbr)
	{
		philo[i].env = env;
		philo[i].id = i + 1;
		philo[i].eat_cnt = 0;
		philo[i].std_eat = 0;
		philo[i].state = 0;
		philo[i].std_sleep = 0;
		philo[i].fork.left = i;
		philo[i].fork.right = (i + 1) % env->args.nbr;
		if (pthread_mutex_init(&philo[i].meal_cnt, NULL) != 0)
			return (NULL);
	}
	return (philo);
}
