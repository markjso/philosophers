/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:00:24 by jmarks            #+#    #+#             */
/*   Updated: 2023/01/20 16:39:25 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *msg)
{
	printf("Error :: %s\n", msg);
	exit(1);
}

int	ft_atoi(char *str)
{
	unsigned long long int	nb;
	int						i;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		print_error(NOT_VALID_ARG);
	return ((int)nb);
}

int	is_a_nbr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
			i++;
	}
	return (1);
}

int	is_valid_input(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (is_a_nbr(av[i]) == 0)
			print_error(NOT_VALID_ARG);
			i++;
	}
	return (1);
}

void	destroy_and_exit(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->number_of_philosophers)
	{
		pthread_mutex_destroy(&arg->ph[i].fork);
		i++;
	}
	pthread_mutex_destroy(&arg->action);
	free(arg->ph);
	exit(0);
}
