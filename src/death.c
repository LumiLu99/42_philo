/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 01:31:48 by yelu              #+#    #+#             */
/*   Updated: 2025/08/29 15:28:19 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	stop_then_print_death(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = true;
	if (!data->winner)
	{
		data->winner = 1;
		pthread_mutex_lock(&data->print_mutex);
		printf(RED"%lld\t%d died\n"RESET,
			get_current_time() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&data->print_mutex);
	}
	pthread_mutex_unlock(&data->stop_mutex);
}

void	*someone_died(void *arg)
{
	t_philo		*philo;
	t_data		*data;
	long long	last_meal_time;

	philo = (t_philo *)arg;
	data = philo->data;
	while (!stop_check_and_full(philo))
	{
		pthread_mutex_lock(&philo->eat_mutex);
		last_meal_time = philo->last_meal_time;
		pthread_mutex_unlock(&philo->eat_mutex);
		if ((get_current_time() - last_meal_time) >= data->time_to_die)
		{
			if (!get_stop(data))
				stop_then_print_death(philo, data);
			break ;
		}
		usleep(100);
	}
	return (NULL);
}

int	stop_check_and_full(t_philo *philo)
{
	bool	stop;
	int		meals_needed;

	pthread_mutex_lock(&philo->eat_mutex);
	meals_needed = philo->meals_eaten;
	pthread_mutex_unlock(&philo->eat_mutex);
	pthread_mutex_lock(&philo->data->stop_mutex);
	stop = philo->data->stop;
	pthread_mutex_unlock(&philo->data->stop_mutex);
	if (meals_needed == 0 || stop == true)
		return (1);
	return (0);
}
