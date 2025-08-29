/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 00:54:18 by yelu              #+#    #+#             */
/*   Updated: 2025/08/29 14:59:30 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	init_user_input(t_data *data, char **argv)
{
	memset(data, 0, (sizeof(t_data)));
	data->number_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->stop = false;
	data->winner = 0;
	if (data->number_of_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (error_exit("All arguments must be positive numbers", 39), 0);
	if (argv[5])
	{
		data->num_meals_needed = ft_atoi(argv[5]);
		if (data->num_meals_needed <= 0)
			return (error_exit("Number of meals must be positive", 33), 0);
	}
	else
		data->num_meals_needed = -1;
	return (1);
}

int	check_valid_int(const char *str)
{
	int			i;
	int			sign;
	long long	sum;
	long long	result;

	i = 0;
	sign = 1;
	sum = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		sum = (sum * 10) + (str[i] - 48);
		result = sum * sign;
		if ((result < INT_MIN) || (result > INT_MAX))
			return (0);
		i++;
	}
	return (1);
}

int	ft_isnum(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '-' || argv[i] == '+')
			return (error_exit("Please enter numbers without signs", 35), 0);
		else if (argv[i] < '0' || argv[i] > '9')
			return (error_exit("Please enter numbers only", 26), 0);
		else
			i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		sum;

	i = 0;
	sign = 1;
	sum = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		sum = (sum * 10) + (str[i] - 48);
		i++;
	}
	return (sum * sign);
}

int	check_input(t_data *data, char **argv)
{
	int		i;

	i = 0;
	while (argv[++i])
	{
		if (!ft_isnum(argv[i]))
			return (0);
		if (!check_valid_int(argv[i]))
			return (error_exit("Please enter num less than INT_MAX", 35), 0);
	}
	if (!init_user_input(data, argv))
		return (0);
	return (1);
}
