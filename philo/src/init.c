/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:19:54 by juzoanya          #+#    #+#             */
/*   Updated: 2022/09/28 20:20:45 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **argv)
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
		return (0);
	env->args.nbr = ft_atoi(argv[1]);
	env->args.tt_die = ft_atoi(argv[2]) * 1000;
	env->args.tt_eat = ft_atoi(argv[3]) * 1000;
	env->args.tt_sleep = ft_atoi(argv[4]) * 1000;
	env->dead = 0;
	env->n_th = -1;
	if (argv[5])
		env->args.nbr_meal = ft_atoi(argv[5]);
	else
		env->args.nbr_meal = -1;
	return (1);
}

void	init_philo(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->args.nbr)
	{
		env->philo[i].id = i + 1;
		env->philo[i].std_eat = 0;
		env->philo[i].eat_cnt = 0;
		env->philo[i].std_sleep = 0;
		env->philo[i].fork.left = i;
		env->philo[i].fork.right = (i + 1) % env->args.nbr;
		env->philo[i].args = env->args;
	}
}

void	init_threads(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->args.nbr)
	{
		pthread_mutex_lock(&env->var_chg);
		env->n_th = i;
		pthread_mutex_unlock(&env->var_chg);
		if (pthread_create(&env->philo[i].th, NULL, &routine, (void *)env) != 0)
			printf("thread creation error!\n");
		usleep(1000);
	}
	if (pthread_create(&env->track, NULL, &checker, (void *)env) != 0)
		printf("thread creation error!\n");
	usleep(1000);
	i = -1;
	while (++i < env->args.nbr)
		if (pthread_join(env->philo[i].th, NULL) != 0)
			printf("thread join error!\n");
	if (pthread_join(env->track, NULL) != 0)
		printf("thread join error!\n");
}
