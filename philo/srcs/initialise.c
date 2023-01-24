/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:54:11 by jmarks            #+#    #+#             */
/*   Updated: 2023/01/20 16:59:04 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_arg *arg)
{
	int	i;

	arg->ph = malloc(sizeof(t_philo) * arg->number_of_philosophers);
	if (!arg->ph)
		return (0);
	i = 0;
	while (i < arg->number_of_philosophers)
	{
		arg->ph[i].philo_id = i + 1;
		arg->ph[i].times_eaten = 0;
		arg->ph[i].arg = arg;
		pthread_mutex_init(&arg->ph[i].fork, NULL);
		if ((i + 1) == arg->number_of_philosophers)
			arg->ph[i].left = &arg->ph[0];
		else
			arg->ph[i].left = &arg->ph[i + 1];
		arg->ph[i].arg = arg;
		i++;
	}
	return (1);
}

void	init_arg(t_arg *arg, char **av)
{
	memset(arg, 0, sizeof(t_arg));
	arg->number_of_philosophers = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		arg->times_philosopher_must_eat = ft_atoi(av[5]);
	}
	else
		arg->times_philosopher_must_eat = INT_MAX;
	arg->all_eaten = 0;
	arg->died = 0;
	if (init_philo(arg) != 1)
		print_error(INIT_ERR);
	pthread_mutex_init(&arg->action, NULL);
	return ;
}

static void	*only_one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_log(philo->arg, philo, FORK);
	ft_usleep(philo->arg->time_to_die * 1000);
	pthread_mutex_unlock(&philo->fork);
	return (NULL);
}

void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->arg->times_philosopher_must_eat == 0)
		return (NULL);
	if (philo->arg->number_of_philosophers == 1)
		return (only_one_philo(philo));
	if (philo->philo_id % 2 == 0)
		usleep(1000);
	while (philo->arg->died != 1)
	{
		philo_activity(philo);
		if (philo->times_eaten >= philo->arg->times_philosopher_must_eat)
		{
			philo->arg->all_eaten = 1;
		}
	}
	return (NULL);
}

int	create_philo_thread(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->number_of_philosophers)
	{
		if (pthread_create(&arg->ph[i].thread_id, NULL, &thread_routine,
				&arg->ph[i]) != 0)
			print_error(INIT_ERR);
		arg->ph[i].last_ate = arg->start_time;
		i++;
	}
	check_if_died(arg);
	i = 0;
	while (i < arg->number_of_philosophers)
	{
		if (pthread_join(arg->ph[i].thread_id, NULL) != 0)
			print_error(INIT_ERR);
		i++;
	}
	return (1);
}
