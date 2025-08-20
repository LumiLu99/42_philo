/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 00:55:42 by yelu              #+#    #+#             */
/*   Updated: 2025/08/19 23:00:21 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(int ms, t_data *data)
{
	long long	start_time;

	start_time = get_current_time();
	while (get_current_time() - start_time < ms)
	{
		pthread_mutex_lock(&data->dead_mutex);
		if (data->stop)
		{
			pthread_mutex_unlock(&data->dead_mutex);
            break ;
		}
		pthread_mutex_unlock(&data->dead_mutex);
		usleep(200);
	}
}
