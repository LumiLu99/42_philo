/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:10:54 by yelu              #+#    #+#             */
/*   Updated: 2025/07/17 19:10:54 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	error_exit(const char *str, int len)
{
	write(2, str, len);
	write(2, "\n", 1);
}

void	clean_up(t_data *data)
{
	int	i;

	i = 0;

	if (data->forks)
	{
		while (i < data->number_of_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	i = 0;
	if (data->philos)
	{
		while (i < data->number_of_philos)
		{
			pthread_mutex_destroy(&data->philos[i].eat_mutex);
			i++;
		}
		free(data->philos);
		data->philos = NULL;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
}

int	print_status(t_philo *p, t_status status)
{
	bool	stop;

	pthread_mutex_lock(&p->data->stop_mutex);
	stop = p->data->stop;
	pthread_mutex_unlock(&p->data->stop_mutex);
	if (stop)
		return (0);
	pthread_mutex_lock(&p->data->print_mutex);
	if (status == DIED)
		printf(RED"%lld\t%d died\n"RESET,
			get_current_time() - p->data->start_time, p->id);
	if (status == EATING)
		printf("%lld\t%d is eating\n",
			get_current_time() - p->data->start_time, p->id);
	if (status == THINKING)
		printf("%lld\t%d is thinking\n",
			get_current_time() - p->data->start_time, p->id);
	if (status == SLEEPING)
		printf("%lld\t%d is sleeping\n",
			get_current_time() - p->data->start_time, p->id);
	if (status == FORK)
		printf("%lld\t%d has taken a fork\n",
			get_current_time() - p->data->start_time, p->id);
	pthread_mutex_unlock(&p->data->print_mutex);
	return (1);
}

void	destroy_forks_philos(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->number_of_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}
