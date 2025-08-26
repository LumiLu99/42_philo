/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 01:02:37 by yelu              #+#    #+#             */
/*   Updated: 2025/08/26 16:21:11 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, FORK);
	ft_usleep(philo->data->time_to_die, philo->data);
	printf(RED"%lld\t%d died\n"RESET, get_current_time()
		- philo->data->start_time, philo->id);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

int	get_stop(t_data *data)
{
	bool	stop;

	pthread_mutex_lock(&data->stop_mutex);
	stop = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}

void	*someone_died(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	philo = (t_philo *)arg;
	data = philo->data;
	long long	last_meal_time;
	int	i_print;

	i_print = 0;
	while (!stop_check_and_full(philo))
	{
		pthread_mutex_lock(&philo->eat_mutex);
		last_meal_time = philo->last_meal_time;
		pthread_mutex_unlock(&philo->eat_mutex);
		if ((get_current_time() - last_meal_time) >= data->time_to_die)
		{
			if (!get_stop(data))
			{
				pthread_mutex_lock(&data->stop_mutex);
				data->stop = true;
				i_print = 1;
				pthread_mutex_unlock(&data->stop_mutex);
			}
			if (i_print)
				printf(RED"%lld\t%d died\n"RESET,
					get_current_time() - philo->data->start_time, philo->id);
			break ;
		}
		usleep(100);
	}
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
	// if (philo->id % 2 == 0)
	// 	delay_offset(philo);
	pthread_create(&waiter, NULL, &someone_died, philo);
	while (!stop_check_and_full(philo))
	{
		eat_routine(philo);
		if (stop_check_and_full(philo))
			break ;
		if (!print_status(philo, SLEEPING))
			break ;
		ft_usleep(philo->data->time_to_sleep, data);
		if (!print_status(philo, THINKING))
			break ;
		delay_offset(philo);
	}
	if (pthread_join(waiter, NULL) != 0)
		printf("Waiter thread join error\n");
	return (NULL);
}

void	eat_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	if (!philo_eats(philo))
		return ;
	if (philo->id %2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

int philo_eats(t_philo *philo)
{
	if (!print_status(philo, FORK))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	if (!print_status(philo, FORK))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	pthread_mutex_lock(&philo->eat_mutex);
	philo->meals_eaten--;
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->eat_mutex);
	if (!print_status(philo, EATING))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	ft_usleep(philo->data->time_to_eat, philo->data);
	return (1);
}

int stop_check_and_full(t_philo *philo)
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

void	delay_offset(t_philo *philo)
{
	long long	offset;

	offset = (philo->data->time_to_die - \
			(get_current_time() - philo->meals_eaten) - \
			philo->data->time_to_eat) / 2;
	if (offset < 0)
		offset = 0;
	ft_usleep(offset, philo->data);
}
