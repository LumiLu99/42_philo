/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 01:02:37 by yelu              #+#    #+#             */
/*   Updated: 2025/08/24 17:50:47 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, LEFT_FORK);
	ft_usleep(philo->data->time_to_die, philo->data);
	printf(RED"%lld\t%d died\n"RESET, get_current_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void *routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	pthread_t	waiter;

	philo = (t_philo *)arg;
	data = philo->data;
	if (data->number_of_philos == 1)
		return (single_philo(philo));
	pthread_create(&waiter, NULL, &someone_died, philo);
	while (!stop_check(philo))
	{
		eat_routine(philo);
		if (!philo->meals_eaten || stop_check(philo))
			break ;
		print_status(philo, SLEEPING);
		ft_usleep(philo->data->time_to_sleep, data);

	}
	if (pthread_join(waiter, NULL) != 0)
		return (NULL);
	return (NULL);
}

void	eat_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(&philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(&philo->left_fork);
	}
	philo_eats(philo);
	if (philo->id %2 == 0)
	{
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
	}
}

void philo_eats(t_philo *philo)
{
	print_status(philo, FORK);
	print_status(philo, FORK);
	pthread_mutex_lock(&philo->eat_mutex);
	philo->meals_eaten--;
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->eat_mutex);
}
