/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 19:40:53 by sho               #+#    #+#             */
/*   Updated: 2022/11/01 18:02:29 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	init_philo(t_info *info)
{
	int		i;
	int		sum_philo;
	t_philo	*philos;

	philos = info->all_philosophers;
	sum_philo = info->sum_of_philo;
	i = 0;
	while (i < info->sum_of_philo)
	{
		philos[i].philo_num = i + 1;
		philos[i].eat_times = 0;
		philos[i].last_eat_time = 0;
		philos[i].left_fork = &info->fork[i];
		philos[i].right_fork = &info->fork[((i + 1) + sum_philo) % sum_philo];
		philos[i].time = &info->time[i];
		philos[i].info = (void *)info;
		philos[i].can_continue = &info->can_continue;
		philos[i].ideal_time = 0;
		if (i % 2)
			philos[i].ideal_time = info->time_to_eat;
		else
			philos[i].ideal_time = 0;
		if (info->sum_of_philo % 2 && i + 1 == info->sum_of_philo)
			philos[i].ideal_time = info->time_to_eat * 2;
		i++;
	}
}

int	init_philosophers(t_info *info, int argc, char **argv)
{
	allocate_args(info, argc, argv);
	info->start_time = get_current_time_in_ms();
	info->can_continue = true;
	info->philos_complete_meal = 0;
	info->all_philosophers = (t_philo *)malloc(sizeof(t_philo)
			* ft_atoi(argv[1]));
	info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->sum_of_philo);
	info->time = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->sum_of_philo);
	info->thread = (pthread_t *)malloc(sizeof(pthread_t) * info->sum_of_philo);
	if (!info->all_philosophers || !info->fork
		|| !info->thread)
		return (print_error_msg("malloc error"));
	return (0);
}

void	allocate_args(t_info *info, int argc, char **argv)
{
	*info = (t_info){
		.sum_of_philo = (int)ft_atoi(argv[1]),
		.time_to_die = ft_atoi(argv[2]),
		.time_to_eat = ft_atoi(argv[3]),
		.time_to_sleep = ft_atoi(argv[4]),
	};
	if (argc == 6)
	{
		info->stop_num = ft_atoi(argv[5]);
		info->need_to_count = true;
	}
}

int	init_mutex(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->sum_of_philo)
	{
		if (pthread_mutex_init(&info->fork[i], NULL) != 0)
			return (print_error_msg("pthread_mutex_init error"));
		if (pthread_mutex_init(&info->time[i], NULL) != 0)
			return (print_error_msg("pthread_mutex_init error"));
		i++;
	}
	if (pthread_mutex_init(&info->end_flag, NULL) != 0)
		return (print_error_msg("pthread_mutex_init error"));
	if (pthread_mutex_init(&info->count_meals, NULL) != 0)
		return (print_error_msg("pthread_mutex_init error"));
	if (pthread_mutex_init(&info->write, NULL) != 0)
		return (print_error_msg("pthread_mutex_init error"));
	return (0);
}
