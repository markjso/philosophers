/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:27:16 by jmarks            #+#    #+#             */
/*   Updated: 2023/01/20 17:01:28 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIED 5

# define ARG_COUNT "Check number of arguments"
# define INIT_ERR "Failed to initialise"
# define NOT_VALID_ARG "Invalid argument. Must be an int between \
0 and 2147483647"

typedef struct s_philo	t_philo;

typedef struct s_arg
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				times_philosopher_must_eat;
	int				start_time;
	int				all_eaten;
	int				died;
	pthread_mutex_t	action;
	t_philo			*ph;
}	t_arg;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				philo_id;
	int				last_ate;
	int				times_eaten;
	pthread_mutex_t	fork;
	struct s_philo	*left;
	t_arg			*arg;
}	t_philo;

int		get_current_time(void);
void	ft_usleep(long long time_to_sleep);
int		ft_atoi(char *str);
int		check_int(char *av);
int		is_a_nbr(char *str);
int		is_valid_input(int ac, char **av);
int		print_error(char *msg);
int		init_philo(t_arg *arg);
void	init_arg(t_arg *arg, char **av);
void	destroy_and_exit(t_arg *arg);
void	philo_activity(t_philo *philo);
void	print_log(t_arg *arg, t_philo *philo, char activity);
int		create_philo_thread(t_arg *arg);
void	check_if_died(t_arg *arg);

#endif