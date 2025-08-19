/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:55:05 by yelu              #+#    #+#             */
/*   Updated: 2025/07/17 11:55:05 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	start_philo(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	data->start_time = get_current_time();
	while (i < data->number_of_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].threads, NULL, &routine, &data->philos[i]) != 0)
		{
			error_exit("Philos creation failed\n", 24);
			pthread_mutex_lock(&data->dead_mutex);
			data->stop = true;
			pthread_mutex_unlock(&data->dead_mutex);
			while (j < i)
			{
				pthread_join(data->philos[j].threads, NULL);
				j++;
			}
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < data->number_of_philos)
	{
		if (pthread_join(data->philos[i].threads, NULL) != 0)
			return (error_exit("Failed to join threads\n", 24), 0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data data;

	if (argc == 5 || argc == 6)
	{
		if (!check_input(&data, argv))
			return (1);
		if (!init_data(&data))
			return (1);
		if (!start_philo(&data))
			return (1);
		success_clean_up(&data);
		// free(data.philos);
	}
	else
		return (error_exit(INV_ARG, 238), 1);
}

// ./philo 5 800 200 200 [5]
// 5 — The number of philosophers
// 800 — The time a philosopher will die if he doesn’t eat
// 200 — The time it takes a philosopher to eat
// 200 — The time it takes a philosopher to sleep
// 7 — Number of times all the philosophers need to eat before terminating the program **
