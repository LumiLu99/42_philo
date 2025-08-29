/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:30:52 by yelu              #+#    #+#             */
/*   Updated: 2025/08/29 22:12:41 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

int	philo_eats(t_philo *philo)
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

void	unlock_two(pthread_mutex_t *left, pthread_mutex_t *right)
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

void	lock_two(pthread_mutex_t *left, pthread_mutex_t *right)
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
