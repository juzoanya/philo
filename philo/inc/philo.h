/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 20:50:57 by juzoanya          #+#    #+#             */
/*   Updated: 2022/09/28 21:21:51 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

typedef struct s_args
{
	int			tt_eat;
	int			tt_sleep;
	int			tt_die;
	int			nbr_meal;
	int			nbr;
}				t_args;

typedef struct s_fork
{
	int			left;
	int			right;
}				t_fork;

typedef struct s_philo
{
	int			id;
	long		std_eat;
	long		std_sleep;
	int			eat_cnt;
	t_fork		fork;
	t_args		args;
	pthread_t	th;
}				t_philo;

typedef struct s_env
{
	int				n_th;
	int				dead;
	long			start;
	t_args			args;
	t_philo			*philo;
	pthread_t		track;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	time;
	pthread_mutex_t	var_chg;
}					t_env;

//error handling function
void	err_handler(int n);

//functions in init.c file
void	init_philo(t_env *env);
void	init_threads(t_env *env);
int		init_args(t_env *env, char **argv);

//functions in main.c file
void	run_philo(t_env *env);
int		clean_philo(t_env *env);

//functions in routine.c file
void	*checker(void *content);
void	*routine(void *content);
int		exec_actions(t_env *env, t_philo *philo);

//functions in tasks.c file
int		lock_left(t_env *env, t_philo *philo);
int		lock_right(t_env *env, t_philo *philo);
void	ft_thinking(t_env *env, t_philo *philo);
void	ft_eating(t_env *env, t_philo *philo);

//functions in utils.c file
long	gettime(void);
int		ft_isdigit(char c);
int		ft_atoi(const char *nptr);
int		is_dead_philo(t_env *env, t_philo *philo);

#endif