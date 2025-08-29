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

	j = -1;
	i = -1;
	data->start_time = get_current_time() + 50;
	while (++i < data->number_of_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].threads,
				NULL, &routine, &data->philos[i]) != 0)
		{
			while (++j < i)
				pthread_join(data->philos[j].threads, NULL);
			return (error_exit("Philos creation failed\n", 24), 0);
		}
	}
	i = -1;
	while (++i < data->number_of_philos)
	{
		if (pthread_join(data->philos[i].threads, NULL) != 0)
			return (error_exit("Failed to join philos\n", 24), 0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (!check_input(&data, argv))
			return (1);
		if (!init_data(&data))
			return (1);
		start_philo(&data);
		clean_up(&data);
	}
	else
		return (error_exit(INV_ARG, 238), 1);
}

// ./philo 5 800 200 200 [5]
// 5 — The number of philosophers
// 800 — The time a philosopher will die if he doesn’t eat
// 200 — The time it takes a philosopher to eat
// 200 — The time it takes a philosopher to sleep
// 7 — Number of times all the philosophers 
// need to eat before terminating the program **
//
//
//
// Old function for one global waiter thread
// ==============================================
// void	*check_death(void *arg)
// {
// 	t_data	*data;
// 	int		i;
// 	long long	current_time;
// 	long long	last_meal;

// 	data = (t_data *)arg;
// 	// printf("I am waiter\n");
// 	while (1)
// 	{
// 		i = 0;
// 		while (i < data->number_of_philos)
// 		{
// 			current_time = get_current_time();
// 			pthread_mutex_lock(&data->philos[i].eat_mutex);
// 			last_meal = data->philos[i].last_meal_time;
// 			pthread_mutex_unlock(&data->philos[i].eat_mutex);
// 			pthread_mutex_lock(&data->dead_mutex);
// 			if (current_time - last_meal > data->time_to_die)
// 			{
// 				pthread_mutex_lock(&data->print_mutex);
// 				// printf(RED"%lld\t%d died\n"RESET,
// 				// 	current_time - data->start_time, data->philos[i].id);
// 				if (!data->stop)
// 					data->stop = true;
// 				pthread_mutex_unlock(&data->dead_mutex);
// 				pthread_mutex_unlock(&data->print_mutex);
// 				return (NULL);
// 			}
// 			pthread_mutex_unlock(&data->dead_mutex);
// 			i++;
// 		}
// 		if (data->stop)
// 			return (NULL);
// 		ft_usleep(2, data);
// 	}
// 	return (NULL);
// }
//
// =====================================================
//
// For printing forks' address
// static int fork_index(const pthread_mutex_t *p,
//                       const pthread_mutex_t *base, int n) {
//     if (!p || !base) return -1;                
//     if (p < base || p >= base + n) return -2;
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