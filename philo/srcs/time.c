/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:50:07 by jmarks            #+#    #+#             */
/*   Updated: 2023/01/23 16:50:10 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	ft_usleep(long long time_to_sleep)
{
	long long	time_end;

	time_end = (get_current_time() * 1000) + time_to_sleep;
	while ((get_current_time() * 1000) <= time_end)
	{
		usleep(100);
	}
}
