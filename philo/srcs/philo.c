/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:35:09 by jmarks            #+#    #+#             */
/*   Updated: 2023/01/20 16:50:25 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_arg	arg;

	if (ac < 5 || ac > 6)
		print_error(ARG_COUNT);
	is_valid_input(ac, av);
	init_arg(&arg, av);
	arg.start_time = get_current_time();
	create_philo_thread(&arg);
	destroy_and_exit(&arg);
}
