/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 23:35:13 by juzoanya          #+#    #+#             */
/*   Updated: 2022/09/26 19:25:49 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_philo(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->args.nbr)
		if (pthread_mutex_destroy(&env->forks[i]) != 0)
			return (0);
	if (pthread_mutex_destroy(&env->print) != 0)
		return (0);
	if (pthread_mutex_destroy(&env->time) != 0)
		return (0);
	if (pthread_mutex_destroy(&env->var_chg) != 0)
		return (0);
	free(env->forks);
	free(env->philo);
	return (1);
}

void	run_philo(t_env *env)
{
	int	i;

	i = -1;
	env->philo = (t_philo *)malloc(sizeof(t_philo) * env->args.nbr);
	if (!env->philo)
		printf("memory allocation error!\n");
	init_philo(env);
	env->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* env->args.nbr);
	if (!env->forks)
		printf("memory allocation error!\n");
	while (++i < env->args.nbr)
		if (pthread_mutex_init(&env->forks[i], NULL) != 0)
			printf("mutex init error!\n");
	if (pthread_mutex_init(&env->print, NULL) != 0)
		printf("mutex init error!\n");
	if (pthread_mutex_init(&env->time, NULL) != 0)
		printf("mutex init error!\n");
	if (pthread_mutex_init(&env->var_chg, NULL) != 0)
		printf("mutex init error!\n");
	init_threads(env);
	return ;
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (argc == 5 || argc == 6)
	{
		if (!init_args(&env, argv))
			err_handler(0);
		run_philo(&env);
		if (clean_philo(&env))
			return (0);
	}
	else
		printf("ERROR: Number of arguments require to run program!\n");
	return (0);
}
