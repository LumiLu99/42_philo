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
	t_data	*data;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	data = philo->data;
	printf("I am philo[%d]\n", philo->id);
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (data->number_of_philos == 1)
		{
			pthread_mutex_lock(&philo[i].left_fork);
			usleep(data->time_to_die);
			data->someone_died = true;
			pthread_mutex_lock(&data->print_mutex);
			printf("He freaking died\n");
			pthread_mutex_lock(&data->print_mutex);
			pthread_mutex_unlock(&philo[i].left_fork);
			break ;
		}
		else if (philo->id % 2 == 0)
		{
			printf("I'm in even philo[%d]\n", philo->id);
		
			pthread_mutex_lock(philo->left_fork);
			
			pthread_mutex_lock(&data->print_mutex);
			printf("Even Philo[%d] has taken left fork\n", philo->id);
			pthread_mutex_unlock(&data->print_mutex);
			
			pthread_mutex_lock(philo->right_fork);			
			pthread_mutex_lock(&data->print_mutex);
			printf("Even Philo[%d] has taken right fork\n", philo->id);
			pthread_mutex_unlock(&data->print_mutex);
			pthread_mutex_lock(&data->print_mutex);
			printf("Philo[%d] is eating", philo->id);
			pthread_mutex_unlock(&data->print_mutex);
			pthread_mutex_lock(&data->eat_mutex);
			philo->last_meal_time = get_current_time();
			pthread_mutex_unlock(&data->eat_mutex);
			usleep(data->time_to_eat);
			pthread_mutex_unlock(philo->right_fork);
			printf("Even Philo [%d] has put down right fork\n", philo->id);
			pthread_mutex_unlock(philo->left_fork);
			printf("Even Philo [%d] has put down left fork\n", philo->id);
			usleep(data->time_to_sleep);
		}
		else
		{
			printf("I'm in odd philo[%d]\n", philo->id);
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(&data->print_mutex);
			printf("Odd Philo [%d] has taken left fork\n", philo->id);
			pthread_mutex_unlock(&data->print_mutex);
			
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(&data->print_mutex);
			printf("Odd Philo [%d] has taken right fork\n", philo->id);
			pthread_mutex_unlock(&data->print_mutex);
			pthread_mutex_lock(&data->print_mutex);
			printf("Philo[%d] is eating", philo->id);
			pthread_mutex_unlock(&data->print_mutex);
			pthread_mutex_lock(&data->eat_mutex);
			philo->last_meal_time = get_current_time();
			pthread_mutex_unlock(&data->eat_mutex);
			usleep(data->time_to_eat);
			pthread_mutex_unlock(philo->right_fork);
			printf("Odd Philo [%d] has put down right fork\n", philo->id);
			pthread_mutex_unlock(philo->left_fork);
			printf("Odd Philo [%d] has put down left fork\n", philo->id);
			usleep(data->time_to_sleep);
		}
	}
	return ((void *)0);
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
			if (data->philos)
				free (data->philos);
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
	return (1);
}

static int	init_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->number_of_philos);
	if (!data->philos)
		return (error_exit("Philos creation failed\n", 24), 0);
	if (!init_forks(data))
		return (error_exit("Forks creation failed\n", 23), 0);
	if (!init_mutexes(data))
		return (error_exit("Mutexes creation failed\n", 25), 0);
	if (!init_philo_struct(data))
		return (0);
	return (1);
}

void	*check_death(void *arg)
{
	t_data *data;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->dead_mutex);
		if (data->someone_died)
		{
			pthread_mutex_unlock(&data->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->dead_mutex);
	}
	return ((void *)0);
}

int	init_philo_struct(t_data *data)
{
	int	i;
	time_t	start_time;

	i = 0;
	start_time = get_current_time() ;
	while (i < data->number_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = (&data->forks[(i + 1) % data->number_of_philos]);
		data->philos[i].data = data;
		data->philos[i].meals_eaten = 0;
		if (pthread_create(&data->philos[i].threads, NULL, &routine, &data->philos[i]) != 0)
			return (error_exit("Philo creation failed\n", 23), 0);
		i++;
	}
	if (data->number_of_philos > 1)
		if (pthread_create(&data->waiter, NULL, &check_death, &data) !=0 )
			return (error_exit("Waiter creation failed\n", 24), 0);
	return (1);
}

static int	philo_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		if (pthread_join(data->philos[i].threads, NULL) != 0)
			return (error_exit("Failed to join philos\n", 24), 0);
		i++;
	}
	if (pthread_join(data->waiter, NULL) != 0)
		return (error_exit("Failed to join waiter\n", 28), 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data data;
	int	i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		if (!check_input(&data, argv))
			return (1);
		if (!init_data(&data))
			return (1);
		// start_philo(&philo);
		if (!philo_join(&data))
			return (1);
		clean_up(&data);
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
