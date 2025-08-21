/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 00:58:06 by yelu              #+#    #+#             */
/*   Updated: 2025/08/21 21:32:05 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// static int fork_index(const pthread_mutex_t *p,
//                       const pthread_mutex_t *base, int n) {
//     if (!p || !base) return -1;                  // not wired / not allocated
//     if (p < base || p >= base + n) return -2;    // out of range
//     return (int)(p - base);
// }

// static void debug_dump_forks(t_data *d) {
//     int n = d->number_of_philos;
//     for (int i = 0; i < n; i++) {
//         t_philo *p = &d->philos[i];
//         int L = fork_index(p->left_fork,  d->forks, n);
//         int R = fork_index(p->right_fork, d->forks, n);
//         printf("Philo %d: L=%p[%d]  R=%p[%d]\n",
//                i+1, (void*)p->left_fork, L, (void*)p->right_fork, R);
//     }
// }

int	init_forks(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->number_of_philos));
	if (!data->forks)
		return (error_exit("Malloc fork failed\n", 20), 0);
	while (i < data->number_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&data->forks[j]);
				j++;
			}
			if (data->forks)
				free (data->forks);
			data->forks = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		destroy_forks_philos(data);
		return (error_exit("Init print mutex failed\n", 25), 0);
	}
  	if (pthread_mutex_init(&data->dead_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		destroy_forks_philos(data);
		return (error_exit("Init dead mutex failed\n", 24), 0);
	}
	pthread_mutex_init(&data->stop_mutex, NULL);
	return (1);
}

int	init_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->number_of_philos);
	if (!(data->philos))
		return (error_exit("Philos creation failed\n", 24), 0);
	if (!init_forks(data))
	{
		free(data->philos);
		data->philos = NULL;
		return (error_exit("Forks creation failed\n", 23), 0);
	}
	if (!init_mutexes(data))
	{
		destroy_forks_philos(data);
		return (error_exit("Mutexes creation failed\n", 25), 0);
	}
	if (!init_philo_struct(data))
	{
		destroy_forks_philos(data);
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->dead_mutex);
		return (0);
	}
	return (1);
}

int	init_philo_struct(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->number_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->number_of_philos];
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].eat_mutex, NULL) != 0)
		{
			while (j < i)
			{
				pthread_mutex_destroy(&data->philos[j].eat_mutex);
				j++;
			}
			return (error_exit("Philo eat mutex failed\n", 24), 0);
		}
		data->philos[i].meals_eaten = data->num_meals_needed;
		i++;
	}
	// debug_dump_forks(data);
	return (1);
}
