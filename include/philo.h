/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:55:07 by yelu              #+#    #+#             */
/*   Updated: 2025/07/17 11:55:07 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

# define RESET	"\033[0m"
# define RED	"\033[1;31m"

typedef struct s_philo
{
	pthread_t		threads;
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_meal_time; // time passed from last meal
} t_philo;

typedef struct s_data
{
	long			number_of_philos;
	int			num_meals_needed;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int			start_time;
	bool		someone_died;
	t_philo		*philos;
} t_data;


// Utils
void	error_exit(const char *str);
long	ft_atol(const char *str);
void	ft_isnum(char *argv);

#endif