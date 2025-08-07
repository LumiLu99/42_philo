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

int	check_input(t_data *data, char **argv)
{
	int		i;
	long	num;

	i = 0;
	while (argv[++i])
	{
		if (!ft_isnum(argv[i]))
			return (0);
		num = ft_atol(argv[i]);
		if (num > INT_MAX || num < INT_MIN)
			return (error_exit("Please input numbers less than INT_MAX"), 0);
	}
	memset(data, 0, (sizeof(t_data)));
	data->number_of_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		data->num_meals_needed = ft_atol(argv[5]);
	else
		data->num_meals_needed = -1;
	return (1);
}

static void *routine(void *arg)
{
    int id = *(int *)arg;
    printf("Hi I am philo [%d]\n", id);
	return (NULL);
}

static void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		data->philos[i].id = i;
		pthread_create(&data->philos[i].threads, NULL, routine, &data->philos[i].id);
		i++;
	}
	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_join(data->philos[i].threads, NULL);
		i++;
	}
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc((sizeof(pthread_mutex_t)*(data->number_of_philos)));
	if (!data->forks)
	{
		error_exit("Fork malloc failed", 19);
		return (0);
	}
	while (i < data->number_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			error_exit("Fork initialization failed", 27);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_philo(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->number_of_philos);
	if (!data->philos)
		error_exit("Malloc failed", 14);
	if (!init_forks(data));
		return (0);
	create_threads(data);
}

int	main(int argc, char **argv)
{
	t_data data;

	if (argc == 5 || argc == 6)
	{
		if (!check_input(&data, argv))
			return (1);
		if (!init_philo(&data));
			return (1);
		// start_philo(&philo);
		free(data.philos);
	}
	else
		error_exit((INV_ARG), 238);
}

// ./philo 5 800 200 200 [5]
// 5 — The number of philosophers
// 800 — The time a philosopher will die if he doesn’t eat
// 200 — The time it takes a philosopher to eat
// 200 — The time it takes a philosopher to sleep
// 7 — Number of times all the philosophers need to eat before terminating the program **