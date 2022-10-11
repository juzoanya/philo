/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 20:50:57 by juzoanya          #+#    #+#             */
/*   Updated: 2022/10/10 22:04:25 by juzoanya         ###   ########.fr       */
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

enum e_states
{
	sleeping = 1,
	eating,
	thinking,
	died
};

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

typedef struct s_env
{
	int				dead;
	long			start;
	t_args			args;
	pthread_t		track;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	access;
	pthread_mutex_t	death;
}					t_env;

typedef struct s_philo
{
	int				id;
	long			std_eat;
	long			std_sleep;
	int				eat_cnt;
	int				state;
	t_fork			fork;
	t_env			*env;
	pthread_mutex_t	meal_cnt;
	pthread_t		th;
}				t_philo;

//error handling function
int		err_handler(int err_code);

//functions in init.c file
t_philo	*init_philo(t_env *env);
int		init_mutex(t_env *env);
int		init_args(t_env *env, char **argv);

//functions in main.c file
void	run_philo(t_env *env, t_philo *philo);
int		clean_philo(t_env *env, t_philo *philo);

//functions in routine.c file
void	*checker(void *content);
void	*routine(void *content);

//functions in tasks.c file
int		lock_left(t_philo *philo);
int		lock_right(t_philo *philo);
void	ft_thinking(t_philo *philo);
void	ft_eating(t_philo *philo);

//functions in libft_utils.c file
int		ft_isdigit(char c);
int		ft_atoi(const char *nptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

//functions in libft_utils.c file
long	gettime(void);
int		state_lock_assign(t_philo *philo, int state);
int		death_lock_assign(t_philo *philo);
int		eat_count_set(t_philo *philo, int i);

#endif