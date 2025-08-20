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

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stddef.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include <string.h>

# define RESET	"\033[0m"
# define RED	"\033[1;31m"
# define INV_ARG "Error: Wrong argument. Please enter only 5 or 6 arguments.\n \
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep>\n \
[OPTIONAL: <number_of_times_a_philo_must_eat_before_terminating>]\n \
Usage: ./philo 5 800 200 200 [5]"

typedef enum s_status
{
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	LEFT_FORK,
	RIGHT_FORK,
}	t_status;

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_philo
{
	pthread_t		threads;
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	eat_mutex;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				number_of_philos;
	int				num_meals_needed;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long long		start_time;
	bool			stop;
	pthread_t		waiter;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	stop_mutex;
}	t_data;

// Utils
void		error_exit(const char *str, int len);
int			check_valid_int(const char *str);
int			ft_isnum(char *argv);
int			check_input(t_data *data, char **argv);
int			ft_atoi(const char *str);
long long	get_current_time(void);
int			init_philo_struct(t_data *data);
void		clean_up(t_data *data);
void		ft_usleep(int ms, t_data *data);
void		*routine(void *arg);
int			init_data(t_data *data);
int			someone_died(t_philo *philo);
int		print_status(t_philo *p, t_status status);
void		destroy_forks_philos(t_data *data);
void	*check_death(void *arg);

#endif
