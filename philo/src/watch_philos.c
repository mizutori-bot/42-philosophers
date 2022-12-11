/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:34:21 by sho               #+#    #+#             */
/*   Updated: 2022/11/01 18:02:37 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*watch_if_need_to_stop(void *arg)
{
	t_info			*info;
	int i;
	long long int	current_time;
	long long int	start_time;
 
	info = (t_info *)arg;
	start_time = get_elapsed_time(info);
	while (1)
	{	
		i = 0;
		if (if_can_continue_true(info))
		{
			while (i < info->sum_of_philo)
			{
				current_time = get_elapsed_time(info);
				if (death_checker(&info->all_philosophers[i], current_time, start_time) == -1)
					break;
				i++;
			}
		}
		else
			break;
		usleep(500);
	}
	return (NULL);
}

int death_checker(t_philo *philo,
				 long long int current_time, long long int start_time)
{
	t_info	*info;
	long long int	last_eat_time;

	info = (t_info *)philo->info;
	pthread_mutex_lock(philo->time);
	last_eat_time = philo->last_eat_time;
	pthread_mutex_unlock(philo->time);
	if (last_eat_time)
	{
		if (kill_philo_if_lapse_death_time_from_lasteat
		(current_time, philo, info, last_eat_time) == -1)
			return (-1);
	}
	else
	{
		if (kill_philo_if_lapse_death_time_from_start
		(current_time, start_time, philo, info) == -1)
			return (-1);
	}
	return (0);
}

int	kill_philo_if_lapse_death_time_from_lasteat(long long int current_time,
												t_philo *philo, t_info *info, long long int last_time_eat)
{
	if (current_time - last_time_eat >= info->time_to_die)
	{
		print_time_and_activity(info, philo->philo_num, NUM_DIE);
		pthread_mutex_lock(&info->end_flag);
		info->can_continue = false;
		pthread_mutex_unlock(&info->end_flag);
		return (-1);
	}
	return (0);
}

int	kill_philo_if_lapse_death_time_from_start(long long int current_time,
					long long int start_time, t_philo *philo, t_info *info)
{
	if (current_time - start_time >= info->time_to_die)
	{
		print_time_and_activity(info, philo->philo_num, NUM_DIE);
		pthread_mutex_lock(&info->end_flag);
		info->can_continue = false;
		pthread_mutex_unlock(&info->end_flag);
		return (-1);
	}
	return (0);
}