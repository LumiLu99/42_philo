/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 01:02:37 by yelu              #+#    #+#             */
/*   Updated: 2025/08/28 00:24:16 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// static inline void smart_think(t_philo *p) 
// {
//     int budget = p->data->time_to_die - p->data->time_to_eat - p->data->time_to_sleep;
//     if (budget > 0)
//         ft_usleep(budget / 2, p->data);  // e.g. 800-200-200=400 -> think ~200ms
//     else
//         ft_usleep(1, p->data);
// }

static inline void	lock_two(pthread_mutex_t *left, pthread_mutex_t *right)
{
	if (left < right)
	{
		pthread_mutex_lock(left);
		pthread_mutex_lock(right);
	}
	else
	{
		pthread_mutex_lock(right);
		pthread_mutex_lock(left);
	}
}

static inline void	unlock_two(pthread_mutex_t *left, pthread_mutex_t *right)
{
	if (left < right)
	{
		pthread_mutex_unlock(right);
		pthread_mutex_unlock(left);
	}
	else
	{
		pthread_mutex_unlock(left);
		pthread_mutex_unlock(right);
	}
}

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

int	get_stop(t_data *data)
{
	bool	stop;

	pthread_mutex_lock(&data->stop_mutex);
	stop = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}

void	*someone_died(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	philo = (t_philo *)arg;
	data = philo->data;
	long long	last_meal_time;
	int	winner;

	winner = 0;
	while (!stop_check_and_full(philo))
	{
		pthread_mutex_lock(&philo->eat_mutex);
		last_meal_time = philo->last_meal_time;
		pthread_mutex_unlock(&philo->eat_mutex);
		if ((get_current_time() - last_meal_time) >= data->time_to_die)
		{
			if (!get_stop(data))
			{
				pthread_mutex_lock(&data->stop_mutex);
				data->stop = true;
				winner = 1;
				pthread_mutex_unlock(&data->stop_mutex);
			}
			if (winner)
			{
				pthread_mutex_lock(&data->print_mutex);
				printf(RED"%lld\t%d died\n"RESET,
					get_current_time() - philo->data->start_time, philo->id);
				pthread_mutex_unlock(&data->print_mutex);
			}
			break ;
		}
		usleep(100);
	}
	return (NULL);
}

void *routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	pthread_t	waiter;

	philo = (t_philo *)arg;
	data = philo->data;
	if (data->number_of_philos == 1)
		return (single_philo(philo));
	while (get_current_time() < data->start_time)
		ft_usleep(1, data);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 5, data);
	pthread_create(&waiter, NULL, &someone_died, philo);
	while (!stop_check_and_full(philo))
	{
		eat_routine(philo);
		if (stop_check_and_full(philo))
			break ;
		print_status(philo, SLEEPING);
			// break ;
		ft_usleep(philo->data->time_to_sleep, data);
		print_status(philo, THINKING);
			// break ;
		ft_usleep(1, data);
	}
	if (pthread_join(waiter, NULL) != 0)
		printf("Waiter thread join error\n");
	return (NULL);
}

void	eat_routine(t_philo *philo)
{
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;

	left = philo->left_fork;
	right = philo->right_fork;
	lock_two(left, right);
	if (!philo_eats(philo))
	{
		unlock_two(left, right);
		return ;
	}
	ft_usleep(philo->data->time_to_eat, philo->data);
	unlock_two(left, right);
}

int philo_eats(t_philo *philo)
{
	if (!print_status(philo, FORK))
		return (0);
	if (!print_status(philo, FORK))
		return (0);
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->eat_mutex);
	if (!print_status(philo, EATING))
		return (0);
	if (philo->data->num_meals_needed > 0)
	{
		pthread_mutex_lock(&philo->eat_mutex);
		if (philo->meals_eaten > 0)
			philo->meals_eaten--;
		pthread_mutex_unlock(&philo->eat_mutex);
	}
	return (1);
}

int stop_check_and_full(t_philo *philo)
{
	bool	stop;
	int		meals_needed;

	pthread_mutex_lock(&philo->eat_mutex);
	meals_needed = philo->meals_eaten;
	pthread_mutex_unlock(&philo->eat_mutex);
	pthread_mutex_lock(&philo->data->stop_mutex);
	stop = philo->data->stop;
	pthread_mutex_unlock(&philo->data->stop_mutex);
	if (meals_needed == 0 || stop == true)
		return (1);
	return (0);
}

