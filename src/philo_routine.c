/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 01:02:37 by yelu              #+#    #+#             */
/*   Updated: 2025/08/29 17:39:19 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*single_philo(t_philo *philo, t_data *data)
{
	while (get_current_time() < data->start_time)
		ft_usleep(1, data);
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, FORK);
	ft_usleep(philo->data->time_to_die, philo->data);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf(RED"%lld\t%d died\n"RESET, get_current_time()
		- philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

static int	sleep_and_think(t_philo *philo, t_data *data)
{
	if (!print_status(philo, SLEEPING))
		return (0);
	ft_usleep(philo->data->time_to_sleep, data);
	if (!print_status(philo, THINKING))
		return (0);
	return (1);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	t_data		*data;
	pthread_t	waiter;

	philo = (t_philo *)arg;
	data = philo->data;
	if (data->number_of_philos == 1)
		return (single_philo(philo, data));
	while (get_current_time() < data->start_time)
		ft_usleep(1, data);
	pthread_create(&waiter, NULL, &someone_died, philo);
	while (!stop_check_and_full(philo))
	{
		eat_routine(philo);
		if (stop_check_and_full(philo))
			break ;
		if (!sleep_and_think(philo, data))
			break ;
		ft_usleep(1, data);
	}
	if (pthread_join(waiter, NULL) != 0)
		return (error_exit("Failed to join waiter\n", 23), NULL);
	return (NULL);
}
