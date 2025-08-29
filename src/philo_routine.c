/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 01:02:37 by yelu              #+#    #+#             */
/*   Updated: 2025/08/29 17:09:10 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*single_philo(t_philo *philo)
{
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

void	*routine(void *arg)
{
	t_philo		*philo;
	t_data		*data;
	pthread_t	waiter;

	philo = (t_philo *)arg;
	data = philo->data;
	if (data->number_of_philos == 1)
		return (single_philo(philo));
	while (get_current_time() < data->start_time)
		ft_usleep(1, data);
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
		ft_usleep(1, data);
	}
	if (pthread_join(waiter, NULL) != 0)
		printf("Waiter thread join error\n");
	return (NULL);
}
