/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:58:58 by sho               #+#    #+#             */
/*   Updated: 2022/11/01 18:02:25 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

int	arg_checker(int argc, char **argv)
{
	if (check_num_of_arg(argc) == -1)
		return (-1);
	if (check_if_args_are_number(argc, argv) == -1)
		return (-1);
	if (check_param_of_each_arg(argc, argv) == -1)
		return (-1);
	return (0);
}

int	check_num_of_arg(int argc)
{
	if (argc != 5 && argc != 6)
		return (print_error_msg("too few or too many arguments"));
	return (0);
}

int	check_param_of_each_arg(int argc, char **argv)
{
	int				sum_of_philo;
	long long int	times_of_eat;
	int				i;

	sum_of_philo = ft_atoi(argv[1]);
	if (0 >= sum_of_philo || sum_of_philo > 200)
		return (print_error_msg("pholo num is out of range"));
	i = 2;
	while (i++ < 4)
	{
		if (check_if_time_is_within_range(ft_atoi(argv[i])) == -1)
			return (print_error_msg("time is out of range"));
	}
	if (argc == 6)
	{
		times_of_eat = ft_atoi(argv[5]);
		if (1 > times_of_eat || times_of_eat > INT_MAX)
			return (print_error_msg("times of eat is out of range"));
	}
	return (0);
}

int	check_if_time_is_within_range(long long int time)
{
	if (60 > time || time > INT_MAX)
		return (-1);
	return (0);
}
