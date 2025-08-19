/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 01:02:37 by yelu              #+#    #+#             */
/*   Updated: 2025/08/19 02:20:56 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, LEFT_FORK);
	ft_usleep(philo->data->time_to_die, philo->data);
	print_status(philo, DIED);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void *routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	bool     stop;

	philo = (t_philo *)arg;
	data = philo->data;
	printf("I am philo[%d]\n", philo->id);
	if (data->number_of_philos == 1)
		return (single_philo(philo));
	while (!someone_died(philo))
	{
		pthread_mutex_lock(&data->dead_mutex);
		stop = data->stop;
		pthread_mutex_unlock(&data->dead_mutex);
		if (stop)
			break ;
		if (!philo->meals_eaten)
			break ;
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, LEFT_FORK);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, RIGHT_FORK);
		pthread_mutex_lock(&philo->eat_mutex);
		philo->last_meal_time = get_current_time();
		pthread_mutex_unlock(&philo->eat_mutex);
		print_status(philo, EATING);
		ft_usleep(data->time_to_eat, data);
		pthread_mutex_lock(&philo->eat_mutex);
		philo->meals_eaten--;
		pthread_mutex_unlock(&philo->eat_mutex);
		print_status(philo, SLEEPING);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		ft_usleep(data->time_to_sleep, data);
		print_status(philo, THINKING);
	}
	return (NULL);
}
