/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:29:29 by jmarks            #+#    #+#             */
/*   Updated: 2023/01/20 16:46:54 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_activity(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_log(philo->arg, philo, FORK);
	pthread_mutex_lock(&philo->left->fork);
	print_log(philo->arg, philo, FORK);
	philo->last_ate = get_current_time();
	print_log(philo->arg, philo, EAT);
	ft_usleep(philo->arg->time_to_eat * 1000);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->left->fork);
	print_log(philo->arg, philo, SLEEP);
	ft_usleep(philo->arg->time_to_sleep * 1000);
	print_log(philo->arg, philo, THINK);
}

void	print_log(t_arg *arg, t_philo *philo, char activity)
{
	int	current_time;

	current_time = (get_current_time() - arg->start_time);
	pthread_mutex_lock(&arg->action);
	if (arg->all_eaten != 1)
	{
		if (activity == FORK)
			printf("%i %d has taken a fork\n", current_time, philo->philo_id);
		if (activity == EAT)
			printf("%i %d is eating\n", current_time, philo->philo_id);
		if (activity == SLEEP)
			printf("%i %d is sleeping\n", current_time, philo->philo_id);
		if (activity == THINK)
			printf("%i %d is thinking\n", current_time, philo->philo_id);
		if (activity == DIED)
			printf("%i %d died\n", current_time, philo->philo_id);
	}
	pthread_mutex_unlock(&arg->action);
}

void	check_if_died(t_arg *arg)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < arg->number_of_philosophers)
		{
			if (get_current_time() - arg->ph->last_ate >= arg->time_to_die)
			{
				arg->died = 1;
				print_log(arg, arg->ph, DIED);
				destroy_and_exit(arg);
			}
			else if (arg->all_eaten == 1)
			{
				destroy_and_exit(arg);
			}
			i++;
		}
	}
}
