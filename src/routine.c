/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 01:02:37 by yelu              #+#    #+#             */
/*   Updated: 2025/08/24 14:38:48 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	stop_check(t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	if (data->stop)
	{
		pthread_mutex_unlock(&data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_mutex);
	return (0);
}

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
	// bool	stop;
	pthread_t	waiter;

	philo = (t_philo *)arg;
	data = philo->data;
	if (data->number_of_philos == 1)
		return (single_philo(philo));
	pthread_create(&waiter, NULL, &someone_died, philo);
	while (!stop_check(data))
	{
		pthread_mutex_unlock(&philo->eat_mutex);
		if (philo->id % 2 != 0)
		{
			usleep(200);
			pthread_mutex_lock(philo->right_fork);
			if (!print_status(philo, RIGHT_FORK))
			{
				pthread_mutex_unlock(philo->right_fork);
				break ;
			}
			pthread_mutex_lock(philo->left_fork);
			if (!print_status(philo, LEFT_FORK))
			{
				pthread_mutex_unlock(philo->right_fork);
				pthread_mutex_unlock(philo->left_fork);
				break ;
			}
			pthread_mutex_lock(&philo->eat_mutex);
			philo->last_meal_time = get_current_time();
			pthread_mutex_unlock(&philo->eat_mutex);
			if (!print_status(philo, EATING))
			{
				pthread_mutex_unlock(philo->right_fork);
				pthread_mutex_unlock(philo->left_fork);
				break ;
			}
			ft_usleep(data->time_to_eat, data);
			pthread_mutex_lock(&philo->eat_mutex);
			philo->meals_eaten--;
			pthread_mutex_unlock(&philo->eat_mutex);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			if (stop_check(data) || (!philo->meals_eaten))
				break ;
			if (!print_status(philo, SLEEPING))
				break ;
			ft_usleep(data->time_to_sleep, data);
			if (!print_status(philo, THINKING))
				break ;
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			if (!print_status(philo, LEFT_FORK))
			{
				pthread_mutex_unlock(philo->left_fork);
				break ;
			}
			pthread_mutex_lock(philo->right_fork);
			if (!print_status(philo, RIGHT_FORK))
			{
				pthread_mutex_unlock(philo->right_fork);
				pthread_mutex_unlock(philo->left_fork);
				break ;
			}
			pthread_mutex_lock(&philo->eat_mutex);
			philo->last_meal_time = get_current_time();
			pthread_mutex_unlock(&philo->eat_mutex);
			if (!print_status(philo, EATING))
			{
				pthread_mutex_unlock(philo->right_fork);
				pthread_mutex_unlock(philo->left_fork);
				break ;
			}
			ft_usleep(data->time_to_eat, data);
			pthread_mutex_lock(&philo->eat_mutex);
			philo->meals_eaten--;
			pthread_mutex_unlock(&philo->eat_mutex);
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			if (stop_check(data) || (!philo->meals_eaten))
				break ;
			if (!print_status(philo, SLEEPING))
				break ;
			ft_usleep(data->time_to_sleep, data);
			if (!print_status(philo, THINKING))
				break ;
			usleep(200);
		}
	}
	pthread_join(waiter, NULL);
	return (NULL);
}
