/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:10:54 by yelu              #+#    #+#             */
/*   Updated: 2025/07/17 19:10:54 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	error_exit(const char *str)
{
	printf(RED"%s\n"RESET, str);
	exit(EXIT_FAILURE);
}

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	sum;

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

void	ft_isnum(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '-' || argv[i] == '+')
			error_exit("Please enter numbers without signs\n");
		else if (argv[i] < '0' || argv[i] > '9')
			error_exit("Please enter numbers only\n");
		else
			i++;
	}
}
