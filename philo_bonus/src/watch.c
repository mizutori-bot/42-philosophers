/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:36:52 by sho               #+#    #+#             */
/*   Updated: 2022/10/06 20:11:25 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philo_bonus.h"

void	*death_watcher(void *arg)
{
	t_philo			*philo;
	t_info			*info;
	long long int	current_time;
	long long int	start_time;

	philo = (t_philo *)arg;
	info = (t_info *)philo->ptr_to_info;
	usleep(225 * (philo->sum_of_philo - philo->philo_num));
	start_time = get_current_time_in_ms();
	while (1)
	{
		current_time = get_current_time_in_ms();
		if (philo->last_eat_time)
			kill_philo_if_lapse_death_time_from_lasteat(current_time, philo);
		else
			kill_philo_if_lapse_death_time_from_start(
				current_time, start_time, philo);
		usleep(500);
	}
	return (NULL);
}

void	kill_philo_if_lapse_death_time_from_lasteat(
		long long int current_time, t_philo *philo)
{
	if (current_time - philo->last_eat_time >= philo->time_to_die)
	{
		sem_wait(philo->write);
		printf("%lld %d %s\n", current_time, philo->philo_num, "died");
		exit(3);
	}
}

void	kill_philo_if_lapse_death_time_from_start(
	long long int current_time, long long int start_time, t_philo *philo)
{
	if (current_time - start_time >= philo->time_to_die)
	{
		sem_wait(philo->write);
		printf("%lld %d %s\n", current_time, philo->philo_num, "died");
		exit(3);
	}
}
