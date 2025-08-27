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

int	someone_died(t_philo *philo)
{
	long long	current_time;
	long long	last_meal;
	bool		stop;

	current_time = get_current_time();
	pthread_mutex_lock(&philo->data->dead_mutex);
	last_meal = philo->last_meal_time;
	stop = philo->data->stop;
	pthread_mutex_unlock(&philo->data->dead_mutex);
	if (stop)
		return (1);
	else if (current_time - last_meal > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->dead_mutex);
		if (!philo->data->stop)
			philo->data->stop = true;
		pthread_mutex_unlock(&philo->data->dead_mutex);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf(RED"%lld\t%d died\n"RESET, current_time - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (1);
	}
	return (0);
}
