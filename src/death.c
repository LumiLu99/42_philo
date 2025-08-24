/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 01:31:48 by yelu              #+#    #+#             */
/*   Updated: 2025/08/24 14:27:18 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*someone_died(void *arg)
{
	t_philo		*philo;
	t_data		*data;
	// long long	current_time;
	// long long	last_meal;

	philo = (t_philo *)arg;
	data = philo->data;
	while (!stop_check(data))
	{
		// pthread_mutex_lock(&data->dead_mutex);
		// if (data->stop)
		// {
		// 	pthread_mutex_unlock(&data->dead_mutex);
		// 	break ;
		// }
		// pthread_mutex_unlock(&data->dead_mutex);
		if (get_current_time() - philo->last_meal_time > data->time_to_die)
		{
			// pthread_mutex_lock(&data->print_mutex);
			printf(RED"%lld\t%d died\n"RESET, get_current_time() - data->start_time, philo->id);
			// pthread_mutex_unlock(&data->print_mutex);
			pthread_mutex_lock(&data->dead_mutex);
			if (!data->stop)
				data->stop = true;
			pthread_mutex_unlock(&data->dead_mutex);
			break ;
		}
		if (!philo->meals_eaten)
			break ;
	}
	return (NULL);
}
