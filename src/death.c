/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 01:31:48 by yelu              #+#    #+#             */
/*   Updated: 2025/08/23 22:41:36 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*someone_died(void *arg)
{
	t_philo		*philo;
	t_data		*data;
	long long	current_time;
	long long	last_meal;

	philo = (t_philo *)arg;
	data = philo->data;
	current_time = get_current_time();
	pthread_mutex_lock(&data->dead_mutex);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&data->dead_mutex);
	if (current_time - last_meal > data->time_to_die)
	{
		pthread_mutex_lock(&data->dead_mutex);
		if (!data->stop)
			data->stop = true;
		pthread_mutex_unlock(&data->dead_mutex);
		printf(RED"%lld\t%d died\n"RESET, current_time - data->start_time, philo->id);
		return (NULL);
	}
	if (data->stop)
		return (NULL);
	else
		return (NULL);
}
