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

	i = 0;
	while (argv[++i])
	{
		if (!ft_isnum(argv[i]))
			return (0);
		if (!check_valid_int(argv[i]))
			return (error_exit("Please enter numbers less than INT_MAX", 39), 0);
	}
	memset(data, 0, (sizeof(t_data)));
	data->number_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->num_meals_needed = ft_atoi(argv[5]);
	else
		data->num_meals_needed = -1;
	return (1);
}

static void *routine(void *arg)
{
	t_philo	*philo;
	pthread_t	waiter;

	philo = (t_philo *)arg;
	// if (pthread_create(&waiter, NULL, &check_death, &philos) != 0)
	// 	return (error_exit("Waiter creation failed\n", 24), (void *)0);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo_died())
	{
		if (data->number_of_philos == 1)
		{
			usleep(data->time_to_die);
			break ;
		}
		is_eating(philo);
		// is_sleeping;
		// is_think;
	}
}

void	is_eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock

	}
}

void	is_thinking(t_philo *philo)
{
	write(1, "is thinking", 12);
}

int	init_forks(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->forks = malloc((sizeof(pthread_mutex_t)*(data->number_of_philos)));
	if (!data->forks)
		return (error_exit("Malloc fork failed\n", 20), 0);
	while (i < data->number_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0);
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&data->forks[j]);
				j++;
			}
			free (data->forks);
			free(data->philos);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_mutexes(t_data *data)
{
	pthread_mutex_init(&data->print_mutex, NULL);
  	pthread_mutex_init(&data->eat_mutex, NULL);
  	pthread_mutex_init(&data->dead_mutex, NULL);
}

static int	init_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->number_of_philos);
	if (!(data->philos))
		return (error_exit("Philos creation failed\n", 24), 0);
	if (!init_forks(data))
		return (error_exit("Forks creation failed\n", 23), 0);
	if (!init_mutexes(data))
		return (error_exit("Mutexes creation failed\n", 25), 0);
	if (!init_philo_struct(data))
		return (0);
	return (1);
}

static int	init_philo_struct(t_data *data)
{
	int	i;
	time_t	start_time;

	i = 0;
	while (i < data->number_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = (&data->forks[i % data->number_of_philos]);
		i++;
	}
}

static int	start_philo(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->number_of_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].threads, NULL, &routine, &data->philos[i]) != 0)
			return (error_exit("Philos creation failed\n", 24), -1);
		i++;
	}
	i = 0;
	while (i < data->number_of_philos)
	{
		if (pthread_join(data->philos[i].threads, NULL) != 0);
			return (error_exit("Failed to join philo threads\n", 24), 0);
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
		free(data.philos);
	}
	else
		error_exit(INV_ARG, 238);
}

// ./philo 5 800 200 200 [5]
// 5 — The number of philosophers
// 800 — The time a philosopher will die if he doesn’t eat
// 200 — The time it takes a philosopher to eat
// 200 — The time it takes a philosopher to sleep
// 7 — Number of times all the philosophers need to eat before terminating the program **
