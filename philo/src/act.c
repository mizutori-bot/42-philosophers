/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:59:29 by sho               #+#    #+#             */
/*   Updated: 2022/11/01 18:02:23 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	take_fork(t_philo *philo, t_info *info, int philo_num)
{		
	pthread_mutex_lock(philo->right_fork);
	print_time_and_activity(info, philo_num, NUM_FORK);

	pthread_mutex_lock(philo->left_fork);
	print_time_and_activity(info, philo_num, NUM_FORK);		
}

void	eat(t_philo *philo, pthread_mutex_t *right_fork,
		pthread_mutex_t *left_fork)
{
	t_info	*info;
	long long int lag;

	lag = 0;
	info = (t_info *)philo->info;

	pthread_mutex_lock(philo->time);
	philo->last_eat_time = get_elapsed_time(info);
	pthread_mutex_unlock(philo->time);
	print_time_and_activity(info, philo->philo_num, NUM_EAT);
	eat_times_checker(philo);
	if (philo->ideal_time != 0)
		lag = philo->ideal_time - get_elapsed_time(info);
	philo->ideal_time = philo->ideal_time + info->time_to_eat;
	wait_philo(info->time_to_eat + lag, info);
	pthread_mutex_unlock(right_fork);
	pthread_mutex_unlock(left_fork);
}

void	eat_times_checker(t_philo *philo)
{
	t_info	*info;

	info = (t_info *)philo->info;
	pthread_mutex_lock(&info->count_meals);
	philo->eat_times++;
	if (info->need_to_count && philo->eat_times
		== info->stop_num)
		info->philos_complete_meal++;
	if (info->philos_complete_meal == info->sum_of_philo)
	{
		pthread_mutex_lock(&info->end_flag);
		info->can_continue = false;
		pthread_mutex_unlock(&info->end_flag);
	}
	pthread_mutex_unlock(&info->count_meals);
}

void	sleep_philo(t_info *info, t_philo *philo, int time_to_sleep)
{
	long long int lag;

	print_time_and_activity(info, philo->philo_num, NUM_SLEEP);
	lag = philo->ideal_time - get_elapsed_time(info);
	philo->ideal_time = philo->ideal_time + time_to_sleep;
	wait_philo(time_to_sleep + lag, info);
}

void	think(t_info *info, t_philo *philo)
{
	long long int lag;
	int wait_time;
	wait_time = 0;
	if (info->sum_of_philo % 2 && info->time_to_sleep < info->time_to_eat * 2)
		wait_time = info->time_to_eat * 3 - (info->time_to_eat + info->time_to_sleep);
	print_time_and_activity(info, philo->philo_num, NUM_THINK);
	lag = philo->ideal_time - get_elapsed_time(info);
	philo->ideal_time = philo->ideal_time + wait_time;
	wait_philo(wait_time + lag, info);
}