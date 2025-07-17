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

#include "include/philo.h"

void	check_input(t_philo	*philo, char **argv)
{
	int		i;
	long	num;

	i = 0;
	while (argv[++i] != NULL)
	{
		ft_isnum(argv[i]);
		num = ft_atol(argv[i]);
		if (num > INT_MAX || num < INT_MIN)
			error_exit("Please input numbers less than INT_MAX\n");
	}
	ft_memset(philo, 0, (sizeof(t_philo)));
	philo->number_of_philos = ft_atol(argv[1]);
	philo->time_to_die = ft_atol(argv[2]);
	philo->time_to_eat = ft_atol(argv[3]);
	philo->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		philo->num_meals_needed = ft_atol(argv[5]);
}

// void	create_threads(t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	while ()
// }

// void	init_philo(t_philo *philo, char **argv, pthread_t *threads)
// {
// 	ft_memset(philo, 0, (sizeof(t_philo)));
// 	philo->number_of_philos = ft_atoi(argv[1]);
// 	philo->threads = threads;
// 	create_threads(philo);
// }

int	main(int argc, char **argv)
{
	t_philo philo;
	// pthread_t	threads[200];

	if (argc == 5 || argc == 6)
	{
		check_input(&philo, argv);
		// init_philo(&philo, argv, threads);
		// start_philo(&philo);
		printf("Good boy good input\n");
	}
	else
		error_exit("Wrong argument\n");
	return (0);
}

// ./philo 5 800 200 200 [5]