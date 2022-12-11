/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 19:23:06 by sho               #+#    #+#             */
/*   Updated: 2022/10/06 19:47:30 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo_bonus.h"

int	take_fork(t_philo *philo)
{
	long long int	current_time;
	t_info			*info;

	info = (t_info *)philo->ptr_to_info;
	sem_wait(philo->eat);
	sem_wait(philo->fork);
	current_time = get_current_time_in_ms();
	print_time_and_activity(info, current_time,
		philo->philo_num, "has taken a fork\n");
	sem_wait(philo->fork);
	current_time = get_current_time_in_ms();
	print_time_and_activity(info, current_time,
		philo->philo_num, "has taken a fork\n");
	sem_post(philo->eat);
	return (0);
}

int	eat(t_philo *philo)
{
	t_info			*info;
	long long int	current_time;

	info = (t_info *)philo->ptr_to_info;
	current_time = get_current_time_in_ms();
	philo->last_eat_time = current_time;
	print_time_and_activity(info, current_time, philo->philo_num, "is eating\n");
	wait_philo(philo, philo->time_to_eat);
	if (philo->need_to_count)
		philo->eat_count++;
	if (philo->need_to_count && philo->eat_count == philo->stop_num)
	{
		sem_post(philo->fork);
		sem_post(philo->fork);
		exit(0);
	}
	sem_post(philo->fork);
	sem_post(philo->fork);
	return (0);
}

int	sleep_philo(t_philo *philo)
{
	t_info			*info;
	long long int	current_time;

	info = (t_info *)philo->ptr_to_info;
	current_time = get_current_time_in_ms();
	print_time_and_activity(info, current_time,
		philo->philo_num, "is sleeping\n");
	wait_philo(philo, info->time_to_sleep);
	return (0);
}

int	think(t_philo *philo)
{
	t_info			*info;
	long long int	current_time;

	info = (t_info *)philo->ptr_to_info;
	current_time = get_current_time_in_ms();
	print_time_and_activity(info,
		current_time, philo->philo_num, "is thinking\n");
	return (0);
}
