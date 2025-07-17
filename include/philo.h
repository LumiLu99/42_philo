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

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits.h>

# define RESET	"\033[0m"
# define RED	"\033[1;31m"

typedef pthread_mutex_t t_mutex;

typedef struct s_fork
{
	t_mutex	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	pthread_t	threads;
	int			id;
	int			number_of_philos;
	int			num_meals_needed;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			start_time;
	long		last_meal_time; // time passed from last meal
	t_fork		*left_fork;
	t_fork		*right_fork;
} t_philo;

// Philo



// Utils
void	error_exit(const char *str);
long	ft_atol(const char *str);
void	ft_isnum(char *argv);

#endif