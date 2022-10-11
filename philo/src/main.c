/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 23:35:13 by juzoanya          #+#    #+#             */
/*   Updated: 2022/10/10 22:10:58 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_philo(t_env *env, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < env->args.nbr)
		if (pthread_mutex_destroy(&env->forks[i]) != 0)
			return (0);
	if (pthread_mutex_destroy(&env->print) != 0)
		return (0);
	if (pthread_mutex_destroy(&env->access) != 0)
		return (0);
	if (pthread_mutex_destroy(&env->death) != 0)
		return (0);
	free(env->forks);
	free(philo);
	return (1);
}

void	run_philo(t_env *env, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < env->args.nbr)
		if (pthread_create(&philo[i].th, NULL, &routine, &philo[i]) != 0)
			printf("thread creation error!\n");
	if (pthread_create(&env->track, NULL, &checker, philo) != 0)
		printf("thread creation error!\n");
	i = -1;
	while (++i < env->args.nbr)
		if (pthread_join(philo[i].th, NULL) != 0)
			printf("thread join error!\n");
	if (pthread_join(env->track, NULL) != 0)
		printf("thread join error!\n");
}

int	main(int argc, char **argv)
{
	t_env	env;
	t_philo	*philo;

	if (argc == 5 || argc == 6)
	{
		if (!init_args(&env, argv))
			return (err_handler(1));
		if (!init_mutex(&env))
			return (err_handler(2));
		philo = init_philo(&env);
		if (!philo)
			return (0);
		run_philo(&env, philo);
		clean_philo(&env, philo);
	}
	else
		return (err_handler(0));
}
