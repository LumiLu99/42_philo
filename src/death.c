/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 01:31:48 by yelu              #+#    #+#             */
/*   Updated: 2025/08/19 00:38:37 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	someone_died(t_philo *philo)
{
	t_data		*data;
	long long	current_time;

	data = philo->data;
	current_time = get_current_time();
	if (current_time - philo->last_meal_time > data->time_to_die)
	{
		pthread_mutex_lock(&data->dead_mutex);
		if (!data->stop)
			data->stop = true;
		pthread_mutex_unlock(&data->dead_mutex);
		printf(RED"Someone died oops\n"RESET);
		return (1);
	}
	return (0);
}
