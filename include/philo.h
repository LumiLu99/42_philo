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
# define INV_ARG "Error: Wrong argument. Please enter only 5 or 6 arguments.\n \
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep>\n \
[OPTIONAL: <number_of_times_a_philo_must_eat_before_terminating>]\n \
Usage: ./philo 5 800 200 200 [5]"

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
	long		number_of_philos;
	int			num_meals_needed;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			start_time;
	bool		someone_died;
	t_philo		*philos;
	pthread_mutex_t	*forks;
} t_data;

// Utils
void	error_exit(const char *str, int len);
long	ft_atol(const char *str);
int		ft_isnum(char *argv);
int		check_input(t_data *data, char **argv);

#endif